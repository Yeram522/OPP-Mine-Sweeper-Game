#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>
#include <time.h>  
#include "Color.h"
#include "Utils.h"
#include "Field.h"

class Screen {

private:
	int width;
	int height;
	int size;
	char* canvas;

public:

	// constructor (생성자 함수) 메모리공간상에 적재되는 순간 호출되는
	Screen(int width = 10, int height = 10)
		: width(width), height(height), canvas(new char[(width + 1) * height])
	{
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

	virtual ~Screen()
	{
		delete[] canvas;
		canvas = nullptr;
		width = 0; height = 0;
	}

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
		canvas[size-1] = '\0';

		for (int i = 0; i < (width + 1) * (height-1); i++)
		{	
			Color::setcolor(White, Green);	
			printf(" | ");
			//if (i == size - 1) Color::setcolor(White, White);
			printf("%c", canvas[i]);
		}
	}

	static void Start_game();
	
	static void Update_UI(const int _time);
	
};