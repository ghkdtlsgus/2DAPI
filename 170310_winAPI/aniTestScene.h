#pragma once
#include "gameNode.h"
#include "camel.h"
class aniTestScene : public gameNode
{
private:
	camel* m_camel;
public:
	aniTestScene();
	~aniTestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

