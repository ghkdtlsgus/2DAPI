#pragma once
#include "singletonBase.h"
class Camera :
	public singletonBase<Camera>
{
public:
	// MAX�� ��µ� ���� ������
	const float CAMERA_MAX_LEFT = 0;
	const float CAMERA_MAX_RIGHT = 2000;
	// ���� ��µǴ� ��ǥ ���� ������
	float Now_X = 0;
	float Now_Y = 0;


	//����ǥ ����Ҷ� X+ȭ����µǴ°� =  MAX RIGHT�� �� 
public:
	// ��ǥ ���� 

private:
	float m_X;
	float m_Y;
public:
	Camera();
	~Camera();

};

