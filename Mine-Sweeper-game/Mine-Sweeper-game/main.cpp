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
		//flag_count = rand() % 11 + 10;//0~10-> (0+10)~(10+10) -> 10 ~20
		flag_count = 5;//디버깅 때문에 5로 지정 해 놓음.
		Field::Set_Field(11 * 10, flag_count, fields);
		Field::Compute_Near_Mine(11 * 10, fields);
	}

	void update() override
	{
		Game2D::Update_UI(this->flag_count);

		draw(pos, fields);

		render();
	}

	void GetClickedField(MOUSE_EVENT_RECORD mer) override
	{
		for (int i = 0; i < this->GetSize(); i++)
		{
			WindowPos fieldpos = fields[i].GetWinpos();
			if (fieldpos.x == mer.dwMousePosition.X && fieldpos.y == mer.dwMousePosition.Y)
				fields[i].Clicked();
		}
	}
	
};

int main()
{
	srand(time(NULL));

	
	TestGame().run();
	
	return 0;
}

