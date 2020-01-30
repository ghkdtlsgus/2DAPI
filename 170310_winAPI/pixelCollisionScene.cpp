#include "stdafx.h"
#include "pixelCollisionScene.h"

pixelCollisionScene::pixelCollisionScene()
{
}

pixelCollisionScene::~pixelCollisionScene()
{
}

HRESULT pixelCollisionScene::init()
{
	IMAGEMANAGER->addImage("��", "images/mountain.bmp", 800, 600, true, RGB(255, 0, 255));

	m_ball = IMAGEMANAGER->addImage("ball", "images/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	m_x = WINSIZEX / 2 - 100;
	m_y = WINSIZEY / 2 + 100;
	m_rc = RectMakeCenter(m_x, m_y, m_ball->getWidth(), m_ball->getHeight());

	//y������ Ž���� �簢��
	m_probrY = m_y + m_ball->getHeight() / 2;

	return S_OK;
}

void pixelCollisionScene::release()
{
}

void pixelCollisionScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_x -= 2.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_x += 2.0f;
	}

	//Ž���� y�� ���������� ������Ʈ
	m_probrY = m_y + m_ball->getHeight() / 2;

	//Ž���� y�� ������ ���Ʒ��� ���ϴ¸�ŭ �˻�
	for (int i = m_probrY - 10; i < m_probrY + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("��")->getMemDC(), m_x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//�� ���Ǹ� ���ε��� ���ϴ� �ȼ��浹 �ȼ������� ����
		if (!(r == 255 && g == 0 && b == 255))
		{
			m_y = i - m_ball->getHeight() / 2;
			break;
		}
	}
	m_rc = RectMakeCenter(m_x, m_y, m_ball->getWidth(), m_ball->getHeight());

}

void pixelCollisionScene::render()
{
	IMAGEMANAGER->findImage("��")->render(getMemDC());

	m_ball->render(getMemDC(), m_rc.left, m_rc.top);

	//������ �簢��
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), m_x, m_probrY, m_x + 10, m_probrY + 10);
	}
}
