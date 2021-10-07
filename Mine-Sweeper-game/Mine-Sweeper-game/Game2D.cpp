#include "Game2D.h"

Input* Input::Instance = nullptr;
bool Game2D::isLooping=true;
WindowPos Input:: ClickedPos;
//-------------
// 
// 
// 
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

//마이크로소프트 제공 함수----------------------------------(약간 수정한 것도 있다.)
void Input::ErrorExit(const char* lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void Input::KeyEventProc(KEY_EVENT_RECORD ker)
{
	Borland::gotoxy(0, 12);
	printf("%s\r", blankChars);
	switch (ker.wVirtualKeyCode) {
	case VK_LBUTTON:
		printf("left button ");
		break;
	case VK_BACK:
		printf("back space");
		break;
	case VK_RETURN:
		printf("enter key");
		break;
	case VK_ESCAPE:
		printf("escape key");
		Game2D::isLooping = false;
		break;
	case VK_UP:
		printf("arrow up");
		break;
	default:
		if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x39)
			printf("Key event: %c ", ker.wVirtualKeyCode - 0x30 + '0');
		else printf("Key event: %c ", ker.wVirtualKeyCode - 0x41 + 'A');
		break;
	}

	Borland::gotoxy(0, 0);
}

void Input::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
	Borland::gotoxy(0, 12);
	printf("%s\r", blankChars);
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press %d %d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
			ClickedPos.x = mer.dwMousePosition.X;
			ClickedPos.y = mer.dwMousePosition.Y;//전역변수에 입력받은 pos 넘겨줌.
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved %d %d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
	Borland::gotoxy(0, 0);
}

void Input::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	Borland::gotoxy(0, 13);
	printf("%s\r", blankChars);
	printf("Resize event: ");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
	Borland::gotoxy(0, 0);
}
//---------------------------------------------------------


void Game2D::run()//자식게임클래스를 실행하는 함수이고 while문을 포함한다.
{
	bool isClear = false;
	//키 입력 변수-------------
	
	Input* input = Input::GetInstance();
	
	//input->Intialize();
	
	//게임 루프 스타트!!
	while (isLooping) {
		if (gameclear())
		{
			Borland::gotoxy(44, 9);
			printf("★★★CLEAR★★★");
			isClear = true;
			break;
		}

		clear();

		input->ReadInput();

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
	isLooping = false;
}
