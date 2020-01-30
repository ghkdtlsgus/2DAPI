#include "stdafx.h"
#include "camel.h"

camel::camel()
{
}

camel::~camel()
{
}

HRESULT camel::init()
{
	
	////�ִϸ��̼� (ó������ ������)
	//m_ani1 = new animation;
	//m_ani1->init(m_camel->getWidth(), m_camel->getHeight(), 75, 89);
	//m_ani1->setDefPlayFrame(true, false);
	//m_ani1->setFPS(1);

	////�迭�� ��Ƽ�
	//int arrAni[] = { 1,2,3,7,8,9 };
	//m_ani2 = new animation;
	//m_ani2->init(m_camel->getWidth(), m_camel->getHeight(), 75, 89);
	//m_ani2->setPlayFrame(arrAni, 6, true);
	//m_ani2->setFPS(1);

	////���� ���ؼ�
	//m_ani3 = new animation;
	//m_ani3->init(m_camel->getWidth(), m_camel->getHeight(), 75, 89);
	//m_ani3->setPlayFrame(1, 5, false, false);
	//m_ani3->setFPS(1);

	m_camel = IMAGEMANAGER->addFrameImage("camel", "images/camel.bmp", 300, 267,4,3, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("ani1", "camel", 10, false, true);

	int arrLen[] = { 1,2,3,7,8 };
	ANIMATIONMANAGER->addAnimation("ani2", "camel", arrLen, 5, 5, true);

	ANIMATIONMANAGER->addAnimation("ani3", "camel", 0, 5, 10, false, true);


	//���۽� ������ �ִϸ��̼� ����
	m_ani = ANIMATIONMANAGER->findAnimation("ani1");

	return S_OK;
}

void camel::release()
{
	//SAFE_DELETE(m_ani1);
	//SAFE_DELETE(m_ani2);
	//SAFE_DELETE(m_ani3);
}

void camel::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//m_ani1->start();
		m_ani = ANIMATIONMANAGER->findAnimation("ani1");
		ANIMATIONMANAGER->start("ani1");
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		m_ani = ANIMATIONMANAGER->findAnimation("ani2");
		ANIMATIONMANAGER->start("ani2");
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		m_ani = ANIMATIONMANAGER->findAnimation("ani3");
		ANIMATIONMANAGER->start("ani3");
	}

	
	
	
}

void camel::render()
{
	m_camel->aniRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, m_ani);
}
