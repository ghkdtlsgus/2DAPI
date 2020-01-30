#include "stdafx.h"
#include "FrameRender.h"



void FrameRender::Update(int  *Frame_X, int  *Frame_Y, int Frame_Max_X, int Frame_Max_Y,int *Count)
{
	
	if (*Count / 10 == 1)
	{
		if (*Frame_Y == Frame_Max_Y && *Frame_X == Frame_Max_X)
		{
			*Frame_Y = 0;
			*Frame_X = 0;
			return;
		}
		if (*Frame_X == Frame_Max_X)
		{
			*Frame_X = 0;
			*Frame_Y += 1;
			return;
		}
		*Count = 0;
		*Frame_X += 1;
		return;
	}
	
	*Count += 1;
	
	
	
}

void FrameRender::XflipUpdate(int * Frame_X, int * Frame_Y, int Frame_Max_X, int Frame_Max_Y, int * Count)
{
	if (*Count / 10 == 1)
	{
		if (*Frame_Y == 0 && *Frame_X == Frame_Max_X)
		{
			*Frame_Y = Frame_Max_Y;
			*Frame_X = 0;
			return;
		}
		if (*Frame_X == Frame_Max_X)
		{
			*Frame_X = 0;
			*Frame_Y -= 1;
			return;
		}
		*Count = 0;
		*Frame_X += 1;
		return;
	}

	*Count += 1;

}

FrameRender::FrameRender()
{
}


FrameRender::~FrameRender()
{
}
