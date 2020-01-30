#include "stdafx.h"
#include "rocket.h"
#include "enemyManager.h"

rocket::rocket()
{
}

rocket::~rocket()
{
}

HRESULT rocket::init()
{
	//로켓이미지(플레이어 구조체) 초기화 및 위치 셋팅
	_player.img = IMAGEMANAGER->addImage("rocket", "images/rocket.bmp", WINSIZEX / 2, WINSIZEY / 2 + 300, 52, 64, true, RGB(255, 0, 255));
	_player.speed = 5.f;
	   
	_missile = new missile;
	_missile->init(500);

	_missileM1 = new missileM1;
	_missileM1->init(10, 600);

	//체력바 초기화
	_maxHP = _currentHP = 100;

	_hpBar = new progressBar;
	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

void rocket::release()
{
	SAFE_DELETE(_missile);
	SAFE_DELETE(_missileM1);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
	
}

void rocket::update()
{
	//왼쪽
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.img->getX() > 0)
	{
		_player.img->setX(_player.img->getX() - _player.speed);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_player.img->getX() + _player.img->getWidth() < WINSIZEX))
	{
		_player.img->setX(_player.img->getX() + _player.speed);
	}
	//위
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player.img->getY() > 0)
	{
		_player.img->setY(_player.img->getY() - _player.speed);
	}
	//아래
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && (_player.img->getY() + _player.img->getHeight() < WINSIZEY))
	{
		_player.img->setY(_player.img->getY() + _player.speed);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missileM1->fire(_player.img->getX() + _player.img->getWidth() / 2, _player.img->getY() - 50);
	}

	_missile->update();
	_missileM1->update();
	collsion();

	_hpBar->setX(_player.img->getX());
	_hpBar->setY(_player.img->getY() - 15);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	//세이브
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		char temp[32];
		vector<string> vStr;
		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));
		vStr.push_back(itoa(_player.img->getX(), temp, 10));
		vStr.push_back(itoa(_player.img->getY(), temp, 10));

		TXTDATA->txtSave("save/rocketData.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		vector<string> vStr(TXTDATA->txtLoad("save/rocketData.txt"));

		_currentHP = stoi(vStr[0]);
		//_currentHP = atoi(vStr[0].c_str());
		_player.img->setX(stoi(vStr[2]));
		_player.img->setY(stoi(vStr[3]));
	}


}

void rocket::render()
{
	_player.img->render(getMemDC(), _player.img->getX(), _player.img->getY());

	_missile->render();
	_missileM1->render();

	_hpBar->render();
}

void rocket::removeMissile(int arrNum)
{
	_missileM1->removeMissile(arrNum);
}

void rocket::collsion()
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_missileM1->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void rocket::hitDamage(float damage)
{
	_currentHP -= damage;
}

