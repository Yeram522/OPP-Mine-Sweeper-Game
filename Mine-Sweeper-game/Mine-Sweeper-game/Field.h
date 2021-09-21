#pragma once
#include <iostream>
#include <Windows.h>

enum field
{
	STATE_DEFUALT, //['v'] 0 : ���� ���� ���� ���� �ʵ�(�⺻ ���� ����)
	STATE_SPOT, //['*'] 1 : ���ڰ� �����ϴ� �ʵ�(���콺 Ŭ�� Ȥ�� gameover �Ǿ��� �� ������)
	STATE_NOTHING, //[' '] 2: �ƹ��͵� ���� �ʵ�(�ֺ� spot ������ 0�϶�)
	STATE_FLAG, //['F'] 3: ����� �����ִ� �ʵ�(���콺 Ŭ���ϸ� ���� ����)
};


class Field {
private:
	char shape;
	int state;

public:
	//������: �ʱ� �ʵ�� ��� defualt ���� ������ �ִ�.
	Field()
		: state(STATE_DEFUALT)
	{
		shape = 'D';
	}

	//return Field Shape : �ڽ��� shape�� ����.
	char GetShape()
	{

		return shape;
	}

	int GetState()
	{
		return state;
	}

	//�ʵ��� ���¸� �ٲ��ش�.
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