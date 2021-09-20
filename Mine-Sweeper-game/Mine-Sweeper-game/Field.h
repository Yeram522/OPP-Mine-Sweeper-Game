#pragma once
#include <iostream>
#include <Windows.h>

class Field {//? defualt:오픈 안됨/ * spot: 지뢰 존재 /   nothing: 아무것도 없음/ F : flag
private:
	char shape;
	int state;

public:
	//생성자: 초기 필드는 모드 defualt 값을 가지고 있다.
	Field()
		: state(0)
	{
		shape = '?';
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
	void Changestate()
	{

	}



};