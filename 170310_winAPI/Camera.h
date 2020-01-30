#pragma once
#include "singletonBase.h"
class Camera :
	public singletonBase<Camera>
{
public:
	// MAX로 출력될 왼쪽 오른쪽
	const float CAMERA_MAX_LEFT = 0;
	const float CAMERA_MAX_RIGHT = 2000;
	// 현재 출력되는 좌표 왼쪽 오른쪽
	float Now_X = 0;
	float Now_Y = 0;


	//끝좌표 계산할때 X+화면출력되는값 =  MAX RIGHT면 끝 
public:
	// 좌표 추적 

private:
	float m_X;
	float m_Y;
public:
	Camera();
	~Camera();

};

