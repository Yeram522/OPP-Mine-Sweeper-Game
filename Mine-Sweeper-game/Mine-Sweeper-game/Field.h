#pragma once
#include <iostream>
#include <Windows.h>

enum fieldstate
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
	bool clicked; //Ŭ���� �������� �ƴ���!

public:
	//������: �ʱ� �ʵ�� ��� defualt ���� ������ �ִ�.
	Field()
		: state(STATE_DEFUALT), clicked(false)
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
		this->state = _state;//state�� �ٲ���ٰ� �ؼ� �����Ǵ� shape�� �ٲ����� �ʴ´�!

		if (clicked == false) return; //Ŭ������ �ʾ����� ��� Default ���̴�.
		switch (state)
		{
		case STATE_DEFUALT:
			shape = 'D';
			break;
		case STATE_SPOT:
			shape = '*';
			break;
		case STATE_NOTHING:
			shape = ' ';//���⿡ �Լ��־ ���������� shape����ǰ� �ϱ�.
			break;
		case STATE_FLAG:
			shape = 'F';
			break;
		}
	}

	static void Set_Filed(const int _size, const int _spot, Field* _fields);
	static bool Check_OverLap_Seed(const int* _seeds, const int _seed);
	//�ƹ��͵� ���� �ʵ忡 ���ڸ� ǥ���Ѵ�.
};