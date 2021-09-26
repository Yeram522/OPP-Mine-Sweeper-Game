#include <Screen.h>


void Screen::Start_game()
{
	//ù��° Ŭ���� ���۵Ǹ� �ð��� �帥��.
}

//�ʱ� ���ڸ� ��ġ�Ѵ�.
void Screen::Set_Filed(const int _size, const int _spot, Field* _fields)//�Ű�����: ���� ���ڰ���.
{
	int placed_count= _spot;
	int* seeds = new int[_size]; //������ �ߺ� ������ ���� �� ����.
	memset(seeds, -1, _size);
	while (placed_count > 0)
	{
		int i = (rand() % (_size-1) + 1);// 1 ~ size ����

		if ((i >= 11 && i % 11 == 0) || Check_OverLap_Seed(seeds, i)) continue;
		seeds[_spot - placed_count] = i;
		_fields[i - 1].Changestate(STATE_SPOT);
		placed_count--;
	}
	
	delete[] seeds;
}

//randseed �ߺ� üũ �Լ�: �˻��� ���� �ְ� �ߺ��� ������ false�� ��ȯ�Ѵ�.
bool Screen::Check_OverLap_Seed(const int* _seeds,const int _seed)
{
	int i = 0;
	while (_seeds[i] != -1)
	{
		if (_seeds[i] == _seed) return true;
		i++;
	}

	return false;
}

//�� ��� ������ UI�� ������Ʈ �Ѵ�.
void Screen::Update_UI(const int _time)
{
	Borland::gotoxy(0, 0);
	Color::setcolor(White, Black);
	printf("�ǢǢǢǢ�  Flag: %d || Time: %d  �ǢǢǢǢ�\n", _time , 0 );
	Color::setcolor(White, Green);
	printf("-------------------------------------------");
}