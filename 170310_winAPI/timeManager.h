#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;

public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//한 프레임 경과시간 가져오기 1/60
	float getElapsedTime() const { return _timer->getElapsedTime(); }
	//전체 시간 경과량 가져오기
	float getWorldTime() const { return _timer->getWorldTime(); }
};

