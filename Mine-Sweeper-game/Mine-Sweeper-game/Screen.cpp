#include <Screen.h>


void Screen::Start_game()
{
	//첫번째 클릭이 시작되면 시간이 흐른다.
}

//초기 지뢰를 배치한다.
void Screen::Set_Filed(const int _size, const int _spot, Field* _fields)//매개변수: 랜덤 지뢰개수.
{
	int placed_count= _spot;
	int* seeds = new int[_size]; //랜덤값 중복 방지를 위해 값 저장.
	memset(seeds, -1, sizeof(seeds));
	while (placed_count>0)
	{
		int i = (rand() % _size + 1);// 1 ~ size 까지

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

//randseed 중복 체크 함수: 검사할 값을 넣고 중복이 없으면 true를 반환한다.
bool Screen::Check_OverLap_Seed(int* _seeds,const int _seed)
{
	for (int i = 0; i < sizeof(_seeds); i++)
	{
		if (_seeds[i] == _seed) return false;
	}

	return true;
}

//맨 상단 윗줄의 UI를 업데이트 한다.
void Screen::Update_UI(const int _time)
{
	Borland::gotoxy(0, 0);
	Color::setcolor(White, Black);
	printf("▤▤▤▤▤  Flag: %d || Time: %d  ▤▤▤▤▤\n", _time , 0 );
	Color::setcolor(White, Green);
	printf("-------------------------------------------");
}