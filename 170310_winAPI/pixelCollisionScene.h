#pragma once
#include "gameNode.h"

class pixelCollisionScene : public gameNode
{
private:
	image* m_ball;	//��
	RECT m_rc;

	float m_x, m_y;
	int m_probrY;	//�ȼ��浹 ������ y��


public:
	pixelCollisionScene();
	~pixelCollisionScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

