#pragma once
#include "gameNode.h"
#include "imgData.h"
class Pagedata : public gameNode
{
private:
	imgData* imgDataC;
public:
	int Page;
public:
	HRESULT init();
	void Render();
	void SetPage(int Value) { Page = Value; }
public:
	Pagedata();
	~Pagedata();
};

