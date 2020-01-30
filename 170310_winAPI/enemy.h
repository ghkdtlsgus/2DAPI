#pragma once
#include "gameNode.h"

//���ʹ� �θ� Ŭ���� �� Ŭ������ ��ӹ޾Ƽ� ������ �Ϲݸ��͸� ����

class enemy : public gameNode
{
private:
	image* _image;
	RECT _rc;

	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//�������� �Ѿ� ��Ÿ�� �߰�
	int _fireCount;
	int _rndFireCount;

public:
	enemy();
	virtual ~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void animation();

	bool bulletCountFire();

	RECT getRect() { return _rc; }

};

