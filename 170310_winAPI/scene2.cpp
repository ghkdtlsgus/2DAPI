#include "stdafx.h"
#include "scene2.h"

scene2::scene2()
{
}

scene2::~scene2()
{
}

HRESULT scene2::init()
{
	IMAGEMANAGER->addImage("배경2", "images/배경 화면.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void scene2::release()
{
}

void scene2::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("scene1");
	}
}

void scene2::render()
{
	IMAGEMANAGER->render("배경2", getMemDC());
}
