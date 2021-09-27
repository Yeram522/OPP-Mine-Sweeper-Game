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


extern bool* isLooping;

class Game2D
{
private:
	int width;
	int height;
	int size;
	char* canvas;

public:
	static WindowPos ClickedPos;
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
	static void Start_game();

	static void Update_UI(const int _time);
	static void exit();//while문을 종료한다.
	//--------------------------------------------------------------
	//
	//About KeyBoard and Mouse Input--------------------------------
	static void ErrorExit(const char*);
	static void KeyEventProc(KEY_EVENT_RECORD);
	static void MouseEventProc(MOUSE_EVENT_RECORD);
	static void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	//--------------------------------------------------------------
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