#include <Screen.h>

void Screen::Update_UI()
{
	Borland::gotoxy(0, 0);
	Color::setcolor(Black, White);
	printf("��Flag: %d | Time: %d ��", 10,0);
}