#include "Field.h"

//초기 지뢰를 배치한다.한번만 실행된다.
void Field::Set_Field(const int _size, const int _spot, Field* _fields)//매개변수: 랜덤 지뢰개수.
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

	for (int index = 1; index < _size+1; index++)//배열 field 탐색
	{
		_fields[index - 1].Init_Winpos(index);
		if (_fields[index - 1].GetState() == STATE_SPOT) continue;//지뢰 필드인 경우 탐색하지 않음.

		_fields[index - 1].Changestate(STATE_NOTHING);//지뢰필드가 아닌 부분은 State 변경(to Nothing)
	}

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

//근처에 있는 지뢰 개수를 계산한다.->*********코드 정리 필요********
void Field::Compute_Near_Mine(const int _size,Field* _fields)
{
	//전체필드만큼 반복문을 돌리고,
	//\n인 필드와 *지뢰 필드는 계산에서 제외한다.
	//배열에 초과하는 필드는 거른다.
	for (int index = 1; index < _size + 1; index++)//배열 field 탐색
	{
		if (_fields[index-1].GetState() == STATE_SPOT || (index % 11==0 && index>=11)) continue;//지뢰 필드인 경우 탐색하지 않음.

		for (int point = index - 1; point < index + 2; point++)// |i-1|i|i+1| i를 기준으로 둘레 탐색.
		{
			if (point % 11 == 0 && point>=11) continue;
			
			int up = point - 11 * (point / 11);//11은 width+1 나중에 바꿔줄거임. 보기 쉽게.
			int down = point + 11 * (point / 11);//11은 width+1 나중에 바꿔줄거임. 보기 쉽게.

			if (point < 11)
			{
				up = 0;
				down = point + 11 * (point / 11 + 1);
			}
			
			//1~size 범위에 만족하고 필드에 지뢰가 있으면.
			if (up >= 1 && up < _size-11)
			{
				if (_fields[up - 1].GetState() == STATE_SPOT)
				{
					
					_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
				}
			}
			
			if (down >= 12  && down < _size)
			{
				if (_fields[down - 1].GetState() == STATE_SPOT)
				{
					_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
				}
			}

			if(_fields[point-1].GetState() == STATE_SPOT && point != index) 
				_fields[index - 1].Changestate(_fields[index - 1].GetState() + 1);
		}
	}
	
}



