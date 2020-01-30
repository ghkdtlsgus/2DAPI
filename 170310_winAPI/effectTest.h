#pragma once
#include "gameNode.h"
#include "effect.h"
class effectTest :public gameNode 
{
private:
	effect* m_effect;
	effect* m_effect1;

public:
	effectTest();
	~effectTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

