#include <Screen.h>


void Screen::Start_game()
{
	//ù��° Ŭ���� ���۵Ǹ� �ð��� �帥��.
}


//�� ��� ������ UI�� ������Ʈ �Ѵ�.
void Screen::Update_UI(const int _time)
{
	Borland::gotoxy(0, 0);
	printf("�ǢǢǢǢ�  Flag: %d || Time: %d  �ǢǢǢǢ�\n", _time , 0 );
	printf("-------------------------------------------");
}