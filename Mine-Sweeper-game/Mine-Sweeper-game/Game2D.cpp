#include "Game2D.h"

static HANDLE hStdin;
static DWORD fdwSaveOldMode;
static char blankChars[80];
static bool isLooping = true;

void Game2D::Start_game()
{
	//첫번째 클릭이 시작되면 시간이 흐른다.
}

//맨 상단 윗줄의 UI를 업데이트 한다.
void Game2D::Update_UI(const int _time)
{
	Borland::gotoxy(0, 0);
	printf("▤▤▤▤▤  Flag: %d || Time: %d  ▤▤▤▤▤\n", _time, 0);
	printf("-------------------------------------------");
}

void Game2D::ErrorExit(const char* lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void Game2D::KeyEventProc(KEY_EVENT_RECORD ker)
{
	Borland::gotoxy(0, 11);
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
		isLooping = false;
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

void Game2D::MouseEventProc(MOUSE_EVENT_RECORD mer)
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

void Game2D::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	Borland::gotoxy(0, 13);
	printf("%s\r", blankChars);
	printf("Resize event: ");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
	Borland::gotoxy(0, 0);
}

void Game2D::run()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	memset(blankChars, ' ', 80);
	blankChars[79] = '\0';

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");
	/*
		   Step-1:
		   Disable 'Quick Edit Mode' option programmatically
	 */
	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
	/*
	   Step-2:
	   Enable the window and mouse input events,
	   after you have already applied that 'ENABLE_EXTENDED_FLAGS'
	   to disable 'Quick Edit Mode'
	*/
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");



	while (isLooping) {
		
		clear();

		if (GetNumberOfConsoleInputEvents(hStdin, &cNumRead)) {
			Borland::gotoxy(0, 14);
			printf("number of inputs %d\n", cNumRead);

			if (cNumRead > 0) {

				if (!ReadConsoleInput(
					hStdin,      // input buffer handle
					irInBuf,     // buffer to read into
					128,         // size of read buffer
					&cNumRead)) // number of records read
					ErrorExit("ReadConsoleInput");
				// Dispatch the events to the appropriate handler.

				for (i = 0; i < cNumRead; i++)
				{
					switch (irInBuf[i].EventType)
					{
					case KEY_EVENT: // keyboard input
						KeyEventProc(irInBuf[i].Event.KeyEvent);
						break;

					case MOUSE_EVENT: // mouse input
						MouseEventProc(irInBuf[i].Event.MouseEvent);
						break;

					case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
						ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
						break;

					case FOCUS_EVENT:  // disregard focus events

					case MENU_EVENT:   // disregard menu events
						break;

					default:
						ErrorExit("Unknown event type");
						break;
					}
				}
			}
			Borland::gotoxy(0, 0);
		}


		update();

		Sleep(100);

	}
	printf("\nGame Over\n");

}
