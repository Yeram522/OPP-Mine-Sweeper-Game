#pragma once
#include <iostream>
#include <Windows.h>

class Field {//? defualt:���� �ȵ�/ * spot: ���� ���� /   nothing: �ƹ��͵� ����/ F : flag
private:
	char shape;
	int state;

public:
	//������: �ʱ� �ʵ�� ��� defualt ���� ������ �ִ�.
	Field()
		: state(0)
	{
		shape = '?';
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
	void Changestate()
	{

	}



};