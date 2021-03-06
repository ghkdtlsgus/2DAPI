#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	//������ �ʱ�ȭ
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//�������� �Ѿ� ��Ÿ�� �߰�
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 1000);

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();
	animation();
}

void enemy::render()
{
	draw();
}

void enemy::move()
{
	//����
}

void enemy::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void enemy::animation()
{
	_count++;
	if (_count % 3 == 0)
	{
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

bool enemy::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_rndFireCount = RND->getFromIntTo(1, 1000);
		_fireCount = 0;

		return true;
	}

	return false;
}
