#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Game2D.h"

class TestGame :public Game2D
{
public:
	Field* fields;
	Position pos;
	int flag_count;

	TestGame()
		:Game2D(10,11),fields(new Field[11 * 10]), pos(0, 0),flag_count(0)
	{
		system("mode con cols=80 lines=25 | title Mine Swiper");
		flag_count = rand() % 11 + 10;//0~10-> (0+10)~(10+10) -> 10 ~20
		//flag_count = 5;//����� ������ 5�� ���� �� ����.
		Field::Set_Field(11 * 10, flag_count, fields);
		Field::Compute_Near_Mine(11 * 10, fields);
	}

	void update() override
	{
		Game2D::Update_UI(this->flag_count);

		if (Game2D::IsMouseClicked)
		{
			for (int i = 0; i < 10*11; i++)
			{
				WindowPos fieldpos = fields[i].GetWinpos();//��������
				/*Borland::gotoxy(0, 20);
				printf("Clicked %d %d\n%d %d", fieldpos.x, fieldpos.y, ClickedPos.x, ClickedPos.y);
				Borland::gotoxy(0, 1);*/
				if (fieldpos.x == ClickedPos.x && fieldpos.y == ClickedPos.y)
					fields[i].Clicked();
			}
		}

		draw(pos, fields);

		render();
	}

	
};

int main()
{
	srand(time(NULL));

	
	TestGame().run();
	
	return 0;
}

