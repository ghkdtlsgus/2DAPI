#include "stdafx.h"
#include "aniTestScene.h"

aniTestScene::aniTestScene()
{
}

aniTestScene::~aniTestScene()
{
}

HRESULT aniTestScene::init()
{
	m_camel = new camel;
	m_camel->init();
	return S_OK;
}

void aniTestScene::release()
{
	m_camel->release();
	SAFE_DELETE(m_camel);
}

void aniTestScene::update()
{
	m_camel->update();
}

void aniTestScene::render()
{
	m_camel->render();
}
