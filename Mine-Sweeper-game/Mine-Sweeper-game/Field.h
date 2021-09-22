#pragma once
#include <iostream>
#include <Windows.h>

enum fieldstate
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
	bool clicked; //클릭된 상태인지 아닌지!

public:
	//생성자: 초기 필드는 모드 defualt 값을 가지고 있다.
	Field()
		: state(STATE_DEFUALT), clicked(false)
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
		this->state = _state;//state가 바뀌었다고 해서 렌더되는 shape이 바뀌지는 않는다!

		if (clicked == false) return; //클릭되지 않았으면 계속 Default 값이다.
		switch (state)
		{
		case STATE_DEFUALT:
			shape = 'D';
			break;
		case STATE_SPOT:
			shape = '*';
			break;
		case STATE_NOTHING:
			shape = ' ';//여기에 함수넣어서 숫자정보로 shape저장되게 하기.
			break;
		case STATE_FLAG:
			shape = 'F';
			break;
		}
	}

	static void Set_Filed(const int _size, const int _spot, Field* _fields);
	static bool Check_OverLap_Seed(const int* _seeds, const int _seed);
	//아무것도 없는 필드에 숫자를 표시한다.
};