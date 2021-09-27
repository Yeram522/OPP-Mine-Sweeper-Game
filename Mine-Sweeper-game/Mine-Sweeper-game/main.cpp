#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Game2D.h"

class MineSweeperGame :public Game2D
{
public:
	Field* fields;
	Position pos;
	int flag_count;

	MineSweeperGame()
		:Game2D(10,11),fields(new Field[11 * 10]), pos(0, 0),flag_count(0)
	{
		system("mode con cols=80 lines=25 | title Mine Swiper");
		flag_count = rand() % 11 + 10;//0~10-> (0+10)~(10+10) -> 10 ~20
		Field::Set_Field(11 * 10, flag_count, fields);
		Field::Compute_Near_Mine(11 * 10, fields);
	}

	~MineSweeperGame()
	{ }

	void update() override
	{
		Game2D::Update_UI(this->flag_count);

		if (Game2D::IsMouseClicked)
		{
			for (int i = 0; i < 10*11; i++)
			{
				WindowPos fieldpos = fields[i].GetWinpos();//지역변수
				if (fieldpos.x == ClickedPos.x && fieldpos.y == ClickedPos.y)
				{
					fields[i].Clicked();
					if (fields[i].GetState() == STATE_SPOT) *isLooping = false;
				}
			}
		}

		draw(pos, fields);

		render();
	}

	bool gameclear() override //게임 클리어 조건에 충족했는지 검사한다.
	{
		int sum = 0;
		for (int i = 1; i < 10 * 11+1; i++)
			if (i%11!=0 && fields[i-1].GetIsClicked() == false) sum++;

		if (flag_count != sum) return false;
		*isLooping = false;
		return true;
	
	}
};

int main()
{
	srand(time(NULL));
	MineSweeperGame().run();
	
	return 0;
}

