#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Screen.h"
class TestGame 
{
public:
	Field* fields;
	Position pos;
	Screen screen;
	int flag_count;
	TestGame()
		:fields(new Field[11 * 10]), pos(0, 0), screen(10, 11), flag_count(0)
	{
		system("mode con cols=50 lines=25 | title Mine Swiper");
		//flag_count = rand() % 11 + 10;//0~10-> (0+10)~(10+10) -> 10 ~20
		flag_count = 5;//0~10-> (0+10)~(10+10) -> 10 ~20
		Field::Set_Field(11 * 10, flag_count, fields);
		Field::Compute_Near_Mine(11 * 10, fields);
	}

	int run()
	{
		bool isLooping = true;
		while (isLooping) {
			Screen::Update_UI(this->flag_count);
			

			screen.clear();

			screen.draw(pos, fields);

			screen.render();


			Sleep(100);

			//pos.x = (pos.x + 1) % (screen.getWidth());

		}
		printf("\nGame Over\n");

		return 0;
	}
};

class MineSweeperGame
{
public:
	Field* fields;
	Position pos;
	Screen screen;
	int flag_count;
	MineSweeperGame()
		:fields(new Field[11*11]), pos(0,0), screen(10, 11), flag_count(0)
	{
		system("mode con cols=50 lines=25 | title Mine Swiper");
		flag_count = rand() % 21 + 1;
	}

	int run()
	{
		bool isLooping = true;
		while (isLooping) {
			Screen::Update_UI(flag_count);

			screen.clear();

			screen.draw(pos, fields);

			screen.render();


			Sleep(100);

			//pos.x = (pos.x + 1) % (screen.getWidth());

		}
		printf("\nGame Over\n");

		return 0;
	}
};

int main()
{
	srand(time(NULL));
	system("mode con cols=50 lines=25 | title Mine Swiper");
	
	//MineSweeperGame().run();
	TestGame().run();
	


	return 0;
}

