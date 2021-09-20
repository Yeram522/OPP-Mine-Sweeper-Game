#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <Windows.h>

//클래스와 구조체는 성격이 다르다.
struct Position {
	int x;
	int y; //static변수는 선언과 정의를 동시에 할 수 없다.

	Position(int x = 0, int y = 0) :x(x), y(y) {}//Default 값이 매개변수에 있다.
};

typedef Position Dimension;//이거무슨문법?

class Borland {

public: //클래스->객체화->"변수화" :  Instantiation / 동적할당: 메모리상에 적재/ 클래스(설계도)와 오브젝트(변수화 되는 과정) object instance/ instance 서로다른 공간에 있느것.
	static void initialize()
	{  //static으로 정의된 함수는 "멤버함수"라고 말하지 않는다. 
		//멤버: this라고 하는 포인터 변수에 접근 가능. static은 this라는 정보를 모른다.
		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	}

	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		if (!pos) return;
		gotoxy((*pos).x, (*pos).y);
	}
	static void gotoxy(const Position& pos)
	{
		gotoxy(pos.x, pos.y);
	}
};

#endif 
