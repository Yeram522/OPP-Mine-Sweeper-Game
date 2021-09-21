#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Screen.h"

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
	
	MineSweeperGame().run();
	


	return 0;
}

