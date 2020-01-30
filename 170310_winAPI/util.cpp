#include "stdafx.h"
#include "util.h"


namespace MY_UTIL //본인이 이름 변경해도 상관없음
{
	//두 점사이의 각도
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (endY > startY)
		{
			angle = -angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
}
