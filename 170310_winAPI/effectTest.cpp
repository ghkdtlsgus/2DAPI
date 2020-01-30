#include "stdafx.h"
#include "effectTest.h"

effectTest::effectTest()
{
}

effectTest::~effectTest()
{
}

HRESULT effectTest::init(void)
{
	//���
	IMAGEMANAGER->addImage("���", "images/background.bmp", WINSIZEX, WINSIZEY);

	//���� ����Ʈ
	//IMAGEMANAGER->addImage("����", "images/explosion.bmp", 832, 62, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("����1", "images/explosion1.bmp", 4355, 135, true, RGB(255, 0, 255));

	//m_effect = new effect;
	//m_effect->init(IMAGEMANAGER->findImage("����"), 32, 62, 1, 0.5f);

	//m_effect1 = new effect;
	//m_effect1->init(IMAGEMANAGER->findImage("����1"), 335, 135, 1, 0.3f);

	EFFECTMANAGER->addEffect("����", "images/explosion.bmp", 832, 62, 32, 62, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("����1", "images/explosion1.bmp", 4355, 135, 335, 135, 1, 0.3, 100);

	return S_OK;
}

void effectTest::release(void)
{
	//SAFE_DELETE(m_effect);
	//SAFE_DELETE(m_effect1);
}

void effectTest::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//m_effect->startEffect(_ptMouse.x, _ptMouse.y);
		EFFECTMANAGER->play("����", _ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//m_effect1->startEffect(_ptMouse.x, _ptMouse.y);
		EFFECTMANAGER->play("����1", _ptMouse.x, _ptMouse.y);
	}

	//m_effect->update();
	//m_effect1->update();
}

void effectTest::render(void)
{
	IMAGEMANAGER->render("���", getMemDC());
	//m_effect->render();
	//m_effect1->render();
}
