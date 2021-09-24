#pragma once
#include <iostream>
#include <Windows.h>
#include "Utils.h"

enum fieldstate
{
	//ASCII CODE
	STATE_DEFUALT= 81, //['_'] 0 : ���� ���� ���� ���� �ʵ�(�⺻ ���� ����)
	STATE_SPOT= 42, //['*'] 1 : ���ڰ� �����ϴ� �ʵ�(���콺 Ŭ�� Ȥ�� gameover �Ǿ��� �� ������)
	STATE_NOTHING= 48, //['0'] 2: �ƹ��͵� ���� �ʵ�(�ֺ� spot ������ 0�϶�)
	STATE_FLAG= 70, //['F'] 3: ����� �����ִ� �ʵ�(���콺 Ŭ���ϸ� ���� ����)
};


class Field {
private:
	WindowPos Winpos;
	char shape; //static_cast<char>(fieldstate)
	int state; //fieldstate
	bool Isclicked; //�ʵ尡 Ŭ���� �������� �ƴ���.
	

public:
	//������: �ʱ� �ʵ�� ��� defualt ���� ������ �ִ�.
	Field()
		: state(STATE_DEFUALT), Isclicked(true)
	{
		shape = static_cast<char>(STATE_DEFUALT);
	}

	//private shape ��������� �����Ѵ�.
	char GetShape()
	{
		return shape;
	}

	//private state ��������� �����Ѵ�.
	int GetState()
	{
		return state;
	}

	WindowPos GetWinpos()
	{
		return Winpos;
	}

	//�ʵ��� ���¸� �ٲ��ش�.
	void Changestate(int _state)
	{
		this->state = _state;//state�� �ٲ���ٰ� �ؼ� �����Ǵ� shape�� �ٲ����� �ʴ´�!

		if (Isclicked == false) return; //Ŭ������ �ʾ����� ��� Default ���̴�.
		switch (state)
		{
		case STATE_DEFUALT:
			shape = static_cast<char>(STATE_DEFUALT);
			break;
		case STATE_SPOT:
			shape = static_cast<char>(STATE_SPOT);
			break;
		case STATE_NOTHING:
			shape = static_cast<char>(STATE_NOTHING);//���⿡ �Լ��־ ���������� shape����ǰ� �ϱ�.
			break;
		case STATE_FLAG:
			shape = static_cast<char>(STATE_FLAG);
			break;
		default:
			shape = static_cast<char>(state);
		}
	}

	void Clicked();
	void Init_Winpos(int _index);
	static void Set_Field(const int _size, const int _spot, Field* _fields);
	static bool Check_OverLap_Seed(const int* _seeds, const int _seed);	
	static void Compute_Near_Mine(const int _size, Field* _fields);
};