#include "stdafx.h"
#include "player.h"
player::player()
{
}

player::~player()
{
}

HRESULT player::init(void)
{
	IMAGEMANAGER->addImage("배경", "images/배경.bmp", WINSIZEX * 2, WINSIZEY);
	IMAGEMANAGER->addImage("카메라", "images/카메라.bmp", WINSIZEX / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미니맵", "images/배경.bmp", WINSIZEX * 2 / 10, WINSIZEY / 10);
	IMAGEMANAGER->addImage("미니캐릭", "images/mini.bmp", 3, 4, true, RGB(255, 0, 255));

	_megaman = IMAGEMANAGER->addFrameImage("메가맨", "images/megaman.bmp", 630, 720, 9, 8, true, RGB(255, 0, 255));
	_megaman->setFrameX(0);
	_megaman->setX(WINSIZEX / 2);
	_megaman->setY(WINSIZEY / 2 + 80);

	_alpha = 0;
	_index = 0;
	_count = 1;
	_isLeft = false;
	_camera = 0;
	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _megaman->getX() > 0)
	{
		_isLeft = true;
		_ps = PS_RUN;
		if (_megaman->getX() >= WINSIZEX / 2)
			_megaman->setX(_megaman->getX() - 5);

		else if (_camera < 0) _camera += 5;
		else _megaman->setX(_megaman->getX() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _megaman->getX() + 70 <  WINSIZEX)
	{
		_isLeft = false;
		_ps = PS_RUN;
		if (_megaman->getX() <= WINSIZEX / 2)
			_megaman->setX(_megaman->getX() + 5);

		else if (_camera > -1000) _camera -= 5;
		else _megaman->setX(_megaman->getX() + 5);
	}

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_ps = PS_IDLE;
	}

	_count++;
	if (_isLeft)
	{
		if (_ps == PS_IDLE)
		{
			_megaman->setFrameY(5);
			_megaman->setFrameX(0);
		}

		if (_ps == PS_RUN)
		{
			_megaman->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 8;
				}
				_megaman->setFrameX(_index);
			}
		}
	}

	else
	{

		if (_ps == PS_IDLE)
		{
			_megaman->setFrameY(4);
			_megaman->setFrameX(0);
		}

		if (_ps == PS_RUN)
		{
			_megaman->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
				}
				_megaman->setFrameX(_index);
			}
		}
	}

}

void player::render(void)
{
	IMAGEMANAGER->render("배경", getMemDC(), _camera, 0);
	IMAGEMANAGER->render("미니맵", getMemDC(), 700, 50);
	IMAGEMANAGER->alphaRender("미니캐릭",
		getMemDC(),
		703 + _megaman->getX() / 10 - _camera / 10,
		50 + _megaman->getY() / 10, 155);
	IMAGEMANAGER->render("카메라", getMemDC(),
		700 - _camera / 10, 50);

	_megaman->frameRender(getMemDC(),
		_megaman->getX(),
		_megaman->getY(),
		_megaman->getFrameX(),
		_megaman->getFrameY());
}
