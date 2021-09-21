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
	memset(seeds, -1, sizeof(seeds));
	while (placed_count>0)
	{
		int i = (rand() % _size + 1);// 1 ~ size ����

		if ( (i> 11 && i % 11 != 0) && Check_OverLap_Seed(seeds, i))
		{
			seeds[_spot - placed_count] = i;
			printf("seeds: %d\n", i);
			_fields[i-1].Changestate(STATE_SPOT);
			placed_count--;
		}
	}
	printf("%d\n", placed_count);
	delete[] seeds;
}

//randseed �ߺ� üũ �Լ�: �˻��� ���� �ְ� �ߺ��� ������ true�� ��ȯ�Ѵ�.
bool Screen::Check_OverLap_Seed(int* _seeds,const int _seed)
{
	for (int i = 0; i < sizeof(_seeds); i++)
	{
		if (_seeds[i] == _seed) return false;
	}

	return true;
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