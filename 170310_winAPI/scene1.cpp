#include "stdafx.h"
#include "scene1.h"

scene1::scene1()
{
}

scene1::~scene1()
{
}

HRESULT scene1::init()
{
	IMAGEMANAGER->addImage("배경1", "images/background.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void scene1::release()
{
}

void scene1::update()
{
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("scene2");
	}
}

void scene1::render()
{
	IMAGEMANAGER->render("배경1", getMemDC());
}
