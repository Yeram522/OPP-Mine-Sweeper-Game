#include "Game2D.h"
//-----------�̵���
Input* Input::instance = nullptr;
bool *isLooping;//ecter bool ����.
WindowPos Input:: ClickedPos;
//-------------
 
//�� ��� ������ UI�� ������Ʈ �Ѵ�.
void Game2D::Update_UI(const int _count)
{
	Borland::gotoxy(0, 0);
	printf("�ǢǢǢǢǢǢ�    �� : %d   �ǢǢǢǢǢǢ�\n", _count);
	printf("-------------------------------------------");

	Borland::gotoxy(44, 2);
	printf("How To Game\n");
	Borland::gotoxy(44, 3);
	printf("-------------\n");
	Borland::gotoxy(44, 4);
	printf("Click Mine �� GameOver\n");
	Borland::gotoxy(44, 5);
	printf("LeftMouseClick �� Open the button.\n");
	Borland::gotoxy(44, 6);
	printf("ESC �� End the game\n");
	
}


void Game2D::run()//�ڽİ���Ŭ������ �����ϴ� �Լ��̰� while���� �����Ѵ�.
{
	bool isClear = false;
	//Ű �Է� ����-------------
	
	Input* Instance = Input::GetInstance();//Input instace ����

	//Input::Intialize();

	//���� ���� ��ŸƮ!!
	while (*isLooping) {
		if (gameclear())
		{
			Borland::gotoxy(44, 9);
			printf("�ڡڡ�CLEAR�ڡڡ�");
			isClear = true;
			break;
		}

		clear();

		Instance->ReadInput();

		update();//�ڽ�Ŭ�������� �� �Լ��� �������̵� �Ͽ� ����Ѵ�!

		Sleep(100);

	}

	if (isClear) return;
	
	Borland::gotoxy(44, 9);
	
	printf("��Game-Over��");
	return;
}

void Game2D::exit()
{
	*isLooping = false;
}
