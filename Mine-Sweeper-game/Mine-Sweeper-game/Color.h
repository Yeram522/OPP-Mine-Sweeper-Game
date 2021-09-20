#pragma once
#include <Windows.h>
#include <conio.h>

using namespace std;
enum color4 {
	Black = 0,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	Lgray,
	Dgray,
	Lblue,
	Lgreen,
	Lcyan,
	Lred,
	Lmagenta,
	Yellow,
	White
};

class Color
{
public:
	static void setcolor(int txt, int bg)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);
	}
};