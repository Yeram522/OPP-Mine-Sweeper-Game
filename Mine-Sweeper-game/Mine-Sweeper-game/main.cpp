#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>
#include "Color.h"
#include "Utils.h"

void setcolor(int txt, int bg);

class Field {//? defualt:오픈 안됨/ * spot: 지뢰 존재 /   nothing: 아무것도 없음/ F : flag
private:
	char shape;
	int state;

public:
	//생성자: 초기 필드는 모드 defualt 값을 가지고 있다.
	Field()
		: state(0)
	{
		shape = '?';
	}

	//return Field Shape : 자신의 shape를 리턴.
	char GetShape()
	{
		return shape;
	}

	int GetState()
	{
		return state;
	}

	//필드의 상태를 바꿔준다.
	void Changestate()
	{

	}



};

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

	void draw(const Position& pos,Field* _fields)
	{
		int offset = (width + 1) * pos.y + pos.x;
		for (int i = 0; i < (width + 1) * height; i++)
		{
			const char shape = _fields[i].GetShape();
			strcpy(&canvas[offset+i], &shape);
		}
	}
	
	void render()
	{
		Borland::gotoxy(0, 1);
		for (int h = 0; h < height; h++)
			canvas[(width + 1) * (h + 1) - 1] = '\n';
		canvas[size - 1] = '\0';
		
		for (int i = 0; i < (width + 1) * height; i++)
		{
			if (i == (width + 1) * height - 1) setcolor(White, White);
			else
				setcolor(Green, Green);
			printf("%c", canvas[i]);
			

		}
		      		
	}
};

void setcolor(int txt, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);
}

void Update_UI()
{
	Borland::gotoxy(0, 0);
	setcolor(Black, White);
	printf("Hello");
}

int main()
{
	Field* fields = new Field[20 * 20];
	Position pos = { 0,0 };
	Screen screen(10, 11);
	system("mode con cols=25 lines=25 | title Mine Swiper");
	

	
	bool isLooping = true;
	while (isLooping) {
		Update_UI();
		screen.clear();
		
		screen.draw(pos,fields);

		screen.render();
		
		
		Sleep(100);

		//pos.x = (pos.x + 1) % (screen.getWidth());

	}
	printf("\nGame Over\n");

	return 0;
}

