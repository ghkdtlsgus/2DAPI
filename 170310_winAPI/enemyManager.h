#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "minion.h"

class rocket;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	vEnemy _vMinion;
	viEnemy _viMinion;
	bullet* _bullet;

	rocket* _rocket;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//미니언 셋팅
	void setMinion();

	//미니언 총알발사
	void minionBulletFire();

	vEnemy getVMinion() { return _vMinion; }
	viEnemy getViMinion() { return _viMinion; }

	//미니언 삭제
	void removeMinion(int arrNum);
	//충돌 함수
	void collision();

	//상호참조하기 위해 로켓의 주소값 공유
	void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

