#include "Field.h"

//�ʱ� ���ڸ� ��ġ�Ѵ�.�ѹ��� ����ȴ�.
void Field::Set_Field(const int _size, const int _spot, Field* _fields)//�Ű�����: ���� ���ڰ���.
{
	int placed_count = _spot;
	int* seeds = new int[_size]; //������ �ߺ� ������ ���� �� ����.
	memset(seeds, -1, _size);
	while (placed_count > 0)
	{
		int i = (rand() % (_size - 1) + 1);// 1 ~ size ����

		if ((i >= 11 && i % 11 == 0) || Check_OverLap_Seed(seeds, i)) continue;
		seeds[_spot - placed_count] = i;
		_fields[i - 1].Changestate(STATE_SPOT);
		placed_count--;
	}

	delete[] seeds;

	for (int index = 1; index < _size+1; index++)//�迭 field Ž��
	{
		_fields[index - 1].Init_Winpos(index);
		if (_fields[index - 1].GetState() == STATE_SPOT) continue;//���� �ʵ��� ��� Ž������ ����.

		_fields[index - 1].Changestate(STATE_NOTHING);//�����ʵ尡 �ƴ� �κ��� State ����(to Nothing)
	}

}




//randseed �ߺ� üũ �Լ�: �˻��� ���� �ְ� �ߺ��� ������ false�� ��ȯ�Ѵ�.
bool Field::Check_OverLap_Seed(const int* _seeds, const int _seed)
{
	int i = 0;
	while (_seeds[i] != -1)
	{
		if (_seeds[i] == _seed) return true;
		i++;
	}

	return false;
}

//��ó�� �ִ� ���� ������ ����Ѵ�.->*********�ڵ� ���� �ʿ�********
void Field::Compute_Near_Mine(const int _size,Field* _fields)
{
	//��ü�ʵ常ŭ �ݺ����� ������,
	//\n�� �ʵ�� *���� �ʵ�� ��꿡�� �����Ѵ�.
	//�迭�� �ʰ��ϴ� �ʵ�� �Ÿ���.
	for (int index = 1; index < _size + 1; index++)//�迭 field Ž��
	{
		if (_fields[index-1].GetState() == STATE_SPOT || (index % 11==0 && index>=11)) continue;//���� �ʵ��� ��� Ž������ ����.

		for (int point = index - 1; point < index + 2; point++)// |i-1|i|i+1| i�� �������� �ѷ� Ž��.
		{
			if (point % 11 == 0 && point>=11) continue;
			
			int up = point - 11 * (point / 11);//11�� width+1 ���߿� �ٲ��ٰ���. ���� ����.
			int down = point + 11 * (point / 11);//11�� width+1 ���߿� �ٲ��ٰ���. ���� ����.

			if (point < 11)
			{
				up = 0;
				down = point + 11 * (point / 11 + 1);
			}
			
			//1~size ������ �����ϰ� �ʵ忡 ���ڰ� ������.
			if (up >= 1 && up < _size-11)
			{
				if (_fields[up - 1].GetState() == STATE_SPOT)
				{
					
					_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
				}
			}
			
			if (down >= 12  && down < _size)
			{
				if (_fields[down - 1].GetState() == STATE_SPOT)
				{
					_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
				}
			}

			if(_fields[point-1].GetState() == STATE_SPOT && point != index) 
				_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
		}
	}
	
}



