#include "Field.h"

//초기 지뢰를 배치한다.한번만 실행된다.
void Field::Set_Filed(const int _size, const int _spot, Field* _fields)//매개변수: 랜덤 지뢰개수.
{
	int placed_count = _spot;
	int* seeds = new int[_size]; //랜덤값 중복 방지를 위해 값 저장.
	memset(seeds, -1, _size);
	while (placed_count > 0)
	{
		int i = (rand() % (_size - 1) + 1);// 1 ~ size 까지

		if ((i >= 11 && i % 11 == 0) || Check_OverLap_Seed(seeds, i)) continue;
		seeds[_spot - placed_count] = i;
		_fields[i - 1].Changestate(STATE_SPOT);
		placed_count--;
	}

	delete[] seeds;
}

//randseed 중복 체크 함수: 검사할 값을 넣고 중복이 없으면 false를 반환한다.
bool Field::Check_OverLap_Seed(const int* _seeds, const int _seed)
{
	int i = 0;
	while (_seeds[i] != -1)
	{
		if (_seeds[i] == _seed) return true;
		i++;
	}

	return false;
}