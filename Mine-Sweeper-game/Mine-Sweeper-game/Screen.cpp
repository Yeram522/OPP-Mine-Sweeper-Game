#include <Screen.h>


void Screen::Start_game()
{
	//첫번째 클릭이 시작되면 시간이 흐른다.
}

//초기 지뢰를 배치한다.
void Screen::Set_Filed(int _spot)//매개변수: 랜덤 지뢰개수.
{
	
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