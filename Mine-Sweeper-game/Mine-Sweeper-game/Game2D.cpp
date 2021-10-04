#include "Game2D.h"
//-----------이동완
Input* Input::instance = nullptr;
bool *isLooping;//ecter bool 선언.
WindowPos Input:: ClickedPos;
//-------------
 
//맨 상단 윗줄의 UI를 업데이트 한다.
void Game2D::Update_UI(const int _count)
{
	Borland::gotoxy(0, 0);
	printf("▤▤▤▤▤▤▤    ★ : %d   ▤▤▤▤▤▤▤\n", _count);
	printf("-------------------------------------------");

	Borland::gotoxy(44, 2);
	printf("How To Game\n");
	Borland::gotoxy(44, 3);
	printf("-------------\n");
	Borland::gotoxy(44, 4);
	printf("Click Mine → GameOver\n");
	Borland::gotoxy(44, 5);
	printf("LeftMouseClick → Open the button.\n");
	Borland::gotoxy(44, 6);
	printf("ESC → End the game\n");
	
}


void Game2D::run()//자식게임클래스를 실행하는 함수이고 while문을 포함한다.
{
	bool isClear = false;
	//키 입력 변수-------------
	
	Input* Instance = Input::GetInstance();//Input instace 생성

	//Input::Intialize();

	//게임 루프 스타트!!
	while (*isLooping) {
		if (gameclear())
		{
			Borland::gotoxy(44, 9);
			printf("★★★CLEAR★★★");
			isClear = true;
			break;
		}

		clear();

		Instance->ReadInput();

		update();//자식클래스에서 이 함수를 오버라이드 하여 사용한다!

		Sleep(100);

	}

	if (isClear) return;
	
	Borland::gotoxy(44, 9);
	
	printf("★Game-Over★");
	return;
}

void Game2D::exit()
{
	*isLooping = false;
}
