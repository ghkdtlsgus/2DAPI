#pragma once
#include "gameNode.h"

//에너미 부모 클래스 이 클래스를 상속받아서 보스나 일반몬스터를 만듬

class enemy : public gameNode
{
private:
	image* _image;
	RECT _rc;

	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//랜덤으로 총알 쿨타임 추가
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

