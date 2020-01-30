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

	//�̴Ͼ� ����
	void setMinion();

	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();

	vEnemy getVMinion() { return _vMinion; }
	viEnemy getViMinion() { return _viMinion; }

	//�̴Ͼ� ����
	void removeMinion(int arrNum);
	//�浹 �Լ�
	void collision();

	//��ȣ�����ϱ� ���� ������ �ּҰ� ����
	void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

