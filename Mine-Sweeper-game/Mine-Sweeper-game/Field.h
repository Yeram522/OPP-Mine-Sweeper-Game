#pragma once
#include <iostream>
#include <Windows.h>

enum field
{
	STATE_DEFUALT, //['v'] 0 : 아직 오픈 되지 않은 필드(기본 랜더 셰입)
	STATE_SPOT, //['*'] 1 : 지뢰가 존재하는 필드(마우스 클릭 혹은 gameover 되었을 때 보여줌)
	STATE_NOTHING, //[' '] 2: 아무것도 없는 필드(주변 spot 개수가 0일때)
	STATE_FLAG, //['F'] 3: 깃발이 꽃혀있는 필드(마우스 클릭하면 생성 가능)
};


class Field {
private:
	char shape;
	int state;

public:
	//생성자: 초기 필드는 모드 defualt 값을 가지고 있다.
	Field()
		: state(STATE_DEFUALT)
	{
		shape = 'D';
	}

	//return Field Shape : 자신의 shape를 리턴.
	char GetShape()
	{

		return shape;
	}

	int GetState()
	{
		return state;
	}

	//필드의 상태를 바꿔준다.
	void Changestate(int _state)
	{
		this->state = _state;

		switch (state)
		{
		case STATE_DEFUALT:
			shape = 'D';
			break;
		case STATE_SPOT:
			shape = '*';
			break;
		case STATE_NOTHING:
			shape = ' ';
			break;
		case STATE_FLAG:
			shape = 'F';
			break;
		}
	}

};