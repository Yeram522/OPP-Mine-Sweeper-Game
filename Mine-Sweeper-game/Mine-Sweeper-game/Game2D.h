#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once

#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class 
#include <time.h>
#include "Field.h"

class Game2D;
class Input;

extern bool* isLooping;

class Input
{
private:
	HANDLE hStdin;
    DWORD fdwSaveOldMode;
    char blankChars[80];
    DWORD cNumRead,fdwMode;
    INPUT_RECORD irInBuf[128];
	static Input* instance; //1개의 static instace만 존재한다.

	Input()
	{
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
	}

	~Input()
	{
		SetConsoleMode(hStdin, fdwSaveOldMode);
	}

public:
	static WindowPos ClickedPos;
	
	static Input* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Input();//instace가 없다면 새로 만든다.
		}
		return instance;
	}

	void ReadInput()
	{
		if (!GetNumberOfConsoleInputEvents(hStdin, &cNumRead))
		{
			cNumRead = 0;
			return;
		}
		Borland::gotoxy(0, 14);
		printf("number of inputs %d\n", cNumRead);

		if (cNumRead == 0) return;

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit("ReadConsoleInput");
		// Dispatch the events to the appropriate handler.

		for (int i = 0; i < cNumRead; i++)
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

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}

		Borland::gotoxy(0, 0);

	}

	void ErrorExit(const char* lpszMessage)
	{
		fprintf(stderr, "%s\n", lpszMessage);

		// Restore input mode on exit.

		SetConsoleMode(hStdin, fdwSaveOldMode);

		ExitProcess(0);
	}

	void KeyEventProc(KEY_EVENT_RECORD ker)
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
			*isLooping = false;
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

	void MouseEventProc(MOUSE_EVENT_RECORD mer)
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

	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
	{
		Borland::gotoxy(0, 13);
		printf("%s\r", blankChars);
		printf("Resize event: ");
		printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
		Borland::gotoxy(0, 0);
	}

	bool GetLeftMouseClick(DWORD eventflag)
	{
		if (cNumRead == 0) return false;

		for (int i = 0; i < cNumRead; i++)
		{
			if (irInBuf[i].EventType != MOUSE_EVENT) continue;

			if (irInBuf[i].Event.MouseEvent.dwEventFlags == eventflag)
				return true;
		}
	}
	
	
};

class Game2D//마우스입력 및 루프, 캔버스/UI를 관리하는 부모 클래스이다.
{
private:
	int width;
	int height;
	int size;
	char* canvas;
	

public:	
	static bool IsMouseClicked;

	Game2D(int width = 10, int height = 10)
		: width(width), height(height), canvas(new char[(width + 1) * height])
	{
		
		isLooping = new bool;
		*isLooping = true;

		bool faultyInput = false;
		if (this->width <= 0) {
			this->width = 10;
			faultyInput = true;
		}
		if (this->height <= 0) {
			this->height = 10;
			faultyInput = true;
		}
		size = (this->width + 1) * this->height;
		if (faultyInput == true) {
			delete canvas;
			canvas = new char[size];
		}
	}

	virtual ~Game2D()
	{
		Borland::gotoxy(0, 13);
		//delete[] canvas;
		canvas = nullptr;
		width = 0; height = 0;
	}

	int GetSize()
	{
		return this->size;
	}

	//About Canvas Draw---------------------------------------------
	void clear()
	{
		memset(canvas, ' ', size);
	}

	void draw(const Position& pos, Field* _fields)
	{
		int offset = (width + 1) * pos.y + pos.x;
		for (int i = 0; i < (width + 1) * height; i++)
		{
			const char shape = _fields[i].GetShape();
			strcpy(&canvas[offset + i], &shape);
		}
	}

	void render()
	{
		Borland::gotoxy(0, 2);
		for (int h = 0; h < height; h++)
			canvas[(width + 1) * h - 1] = '\n';
		canvas[size - 1] = '\0';

		for (int i = 0; i < (width + 1) * (height - 1); i++)
		{

			printf(" | ");

			printf("%c", canvas[i]);
		}
	}
	//--------------------------------------------------------------

	//About Game Logic/Init-----------------------------------------
	static void Update_UI(const int _time);//콘솔 맨 윗줄 UI를 업데이트한다.
	static void exit();//while문을 종료한다.
	//--------------------------------------------------------------
	//
	
	// 
	//Can Override in Sibling Class----------------------------------
	void run();

	virtual void update()
	{
		//Game2D::Update_UI(this->flag_count);
		//draw(pos, fields);
		//render();
	}

	virtual bool gameclear() { return false; }

};