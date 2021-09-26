#pragma once
#include <iostream>
#include <Windows.h>
#include "Utils.h"

enum fieldstate
{
	//ASCII CODE
	STATE_DEFUALT= 81, //['_'] 0 : 아직 오픈 되지 않은 필드(기본 랜더 셰입)
	STATE_SPOT= 42, //['*'] 1 : 지뢰가 존재하는 필드(마우스 클릭 혹은 gameover 되었을 때 보여줌)
	STATE_NOTHING= 48, //['0'] 2: 아무것도 없는 필드(주변 spot 개수가 0일때)
	STATE_FLAG= 70, //['F'] 3: 깃발이 꽃혀있는 필드(마우스 클릭하면 생성 가능)
};


class Field {
private:
	WindowPos Winpos;
	char shape; //static_cast<char>(fieldstate)
	int state; //fieldstate
	bool Isclicked; //필드가 클릭된 상태인지 아닌지.
	

public:
	//생성자: 초기 필드는 모두 defualt 값을 가지고 있다.
	Field()
		: state(STATE_DEFUALT), Isclicked(false), Winpos(0,0)
	{
		shape = static_cast<char>(STATE_DEFUALT);
	}

	//private shape 멤버변수에 접근한다.
	char GetShape()
	{
		return shape;
	}

	//private state 멤버변수에 접근한다.
	int GetState()
	{
		return state;
	}

	WindowPos GetWinpos()
	{
		return Winpos;
	}

	void Init_Winpos(int _index)
	{
		Winpos.x = 3 + (_index - (_index / 11) * 11 - 1) * 4;
		Winpos.y = _index / 11 + 2;
	}

	//필드의 상태를 바꿔준다.
	void Changestate(int _state)
	{
		state = _state;//state가 바뀌었다고 해서 렌더되는 shape이 바뀌지는 않는다!

		if (Isclicked == false) return; //클릭되지 않았으면 계속 Default 값이다.
		switch (state)
		{
		case STATE_DEFUALT:
			shape = static_cast<char>(STATE_DEFUALT);
			break;
		case STATE_SPOT:
			shape = static_cast<char>(STATE_SPOT);
			break;
		case STATE_NOTHING:
			shape = static_cast<char>(STATE_NOTHING);//숫자정보로 shape저장되게 하기.
			break;
		case STATE_FLAG:
			shape = static_cast<char>(STATE_FLAG);
			break;
		default:
			shape = static_cast<char>(state);
		}
	}

	void Clicked()
	{
		Isclicked = true;
		Changestate(state);
	}

	
	static void Set_Field(const int _size, const int _spot, Field* _fields);
	static bool Check_OverLap_Seed(const int* _seeds, const int _seed);	
	static void Compute_Near_Mine(const int _size, Field* _fields);
};