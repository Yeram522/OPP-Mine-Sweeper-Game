#pragma once
#include "Utils.h"

enum fieldstate
{
	//ASCII CODE
	STATE_DEFUALT= 45, //['_'] 0 : ���� ���� ���� ���� �ʵ�(�⺻ ���� ����)
	STATE_SPOT= 42, //['*'] 1 : ���ڰ� �����ϴ� �ʵ�(���콺 Ŭ�� Ȥ�� gameover �Ǿ��� �� ������)
	STATE_NOTHING= 48, //['0'] 2: �ƹ��͵� ���� �ʵ�(�ֺ� spot ������ 0�϶�)
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
		: state(STATE_DEFUALT), Isclicked(false), Winpos(0,0)
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

	bool GetIsClicked()
	{
		return Isclicked;
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

	//�ʵ��� ���¸� �ٲ��ش�.
	void Changestate(int _state)
	{
		state = _state;//state�� �ٲ���ٰ� �ؼ� �����Ǵ� shape�� �ٲ����� �ʴ´�!

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
			shape = static_cast<char>(STATE_NOTHING);//���������� shape����ǰ� �ϱ�.
			break;
		default:
			shape = static_cast<char>(state);
		}
	}

	void Clicked()//�ʵ尡 Ŭ���Ǹ� ����ȴ�.
	{
		if (Isclicked != false)return;
		Isclicked = true;
		Changestate(state);
	}


	static void Set_Field(const int _size, const int _spot, Field* _fields);
	static bool Check_OverLap_Seed(const int* _seeds, const int _seed);	
	static void Compute_Near_Mine(const int _size, Field* _fields);
};