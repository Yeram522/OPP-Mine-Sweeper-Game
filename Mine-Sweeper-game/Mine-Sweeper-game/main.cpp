#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Game2D.h"

class TestGame :public Game2D
{
public:
	Field* fields;
	Position pos;
	//Screen screen;//Game2D로 합치고 부모 클래스가 됨. 부모클래스 생성자에서 초기화.
	int flag_count;

	TestGame()
		:Game2D(10,11),fields(new Field[11 * 10]), pos(0, 0),flag_count(0)
	{
		system("mode con cols=50 lines=25 | title Mine Swiper");
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
	
};

int main()
{
	srand(time(NULL));
	system("mode con cols=50 lines=25 | title Mine Swiper");
	
	TestGame().run();
	
	return 0;
}

