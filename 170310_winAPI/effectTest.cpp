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
	//¹è°æ
	IMAGEMANAGER->addImage("¹è°æ", "images/background.bmp", WINSIZEX, WINSIZEY);

	//Æø¹ß ÀÌÆåÆ®
	//IMAGEMANAGER->addImage("Æø¹ß", "images/explosion.bmp", 832, 62, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Æø¹ß1", "images/explosion1.bmp", 4355, 135, true, RGB(255, 0, 255));

	//m_effect = new effect;
	//m_effect->init(IMAGEMANAGER->findImage("Æø¹ß"), 32, 62, 1, 0.5f);

	//m_effect1 = new effect;
	//m_effect1->init(IMAGEMANAGER->findImage("Æø¹ß1"), 335, 135, 1, 0.3f);

	EFFECTMANAGER->addEffect("Æø¹ß", "images/explosion.bmp", 832, 62, 32, 62, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("Æø¹ß1", "images/explosion1.bmp", 4355, 135, 335, 135, 1, 0.3, 100);

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
		EFFECTMANAGER->play("Æø¹ß", _ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//m_effect1->startEffect(_ptMouse.x, _ptMouse.y);
		EFFECTMANAGER->play("Æø¹ß1", _ptMouse.x, _ptMouse.y);
	}

	//m_effect->update();
	//m_effect1->update();
}

void effectTest::render(void)
{
	IMAGEMANAGER->render("¹è°æ", getMemDC());
	//m_effect->render();
	//m_effect1->render();
}
