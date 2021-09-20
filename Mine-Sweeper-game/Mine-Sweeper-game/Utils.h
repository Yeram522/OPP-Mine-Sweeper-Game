#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <Windows.h>

//Ŭ������ ����ü�� ������ �ٸ���.
struct Position {
	int x;
	int y; //static������ ����� ���Ǹ� ���ÿ� �� �� ����.

	Position(int x = 0, int y = 0) :x(x), y(y) {}//Default ���� �Ű������� �ִ�.
};

typedef Position Dimension;//�̰Ź�������?

class Borland {

public: //Ŭ����->��üȭ->"����ȭ" :  Instantiation / �����Ҵ�: �޸𸮻� ����/ Ŭ����(���赵)�� ������Ʈ(����ȭ �Ǵ� ����) object instance/ instance ���δٸ� ������ �ִ���.
	static void initialize()
	{  //static���� ���ǵ� �Լ��� "����Լ�"��� ������ �ʴ´�. 
		//���: this��� �ϴ� ������ ������ ���� ����. static�� this��� ������ �𸥴�.
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