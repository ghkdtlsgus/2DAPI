#pragma once
#include "singletonBase.h"
#include <time.h>

//==========================================
//	## randomFunction ## (rand() 함수)
//==========================================
class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}
	
	//getInt
	inline int getInt(int num) { return rand() % num; }
	//0 나오면 터지기떄문에 + 1
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};