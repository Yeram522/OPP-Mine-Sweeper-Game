#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>
#include "Color.h"
#include "Utils.h"
#include "Screen.h"
#include "Field.h"


int main()
{
	Field* fields = new Field[20 * 20];
	Position pos = { 0,0 };
	Screen screen(10, 11);
	system("mode con cols=25 lines=25 | title Mine Swiper");
	
	
	bool isLooping = true;
	while (isLooping) {
		Screen::Update_UI();

		screen.clear();
		
		screen.draw(pos,fields);

		screen.render();
		
		
		Sleep(100);

		//pos.x = (pos.x + 1) % (screen.getWidth());

	}
	printf("\nGame Over\n");

	return 0;
}

