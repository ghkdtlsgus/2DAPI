#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//��ȣ������ �� �Ŵ��� Ŭ���� ���漱��
class enemyManager;

struct tagPlayer
{
	image* img;
	float speed;
};

class rocket : public gameNode
{
private:
	tagPlayer _player;	//�÷��̾� ����ü
	missile* _missile;	//�̻��� Ŭ����
	missileM1* _missileM1;

	progressBar* _hpBar;
	float _maxHP;
	float _currentHP;

	enemyManager* _em;	//���ʹ� �Ŵ��� Ŭ���� ���� �ϱ�

public:
	rocket();
	~rocket();

	HRESULT init();
	void release();
	void update();
	void render();

	//�̻��� ����
	void removeMissile(int arrNum);
	//�浹�Լ�
	void collsion();
	//���� ��� �Լ�
	void hitDamage(float damage);

	//���� �̹��� ��������
	image* getRocketImage() { return _player.img; }

	//�̻��� M1 ��������
	missileM1* getMissile() { return _missileM1; }

	//��ȣ�����ϱ� ���� ���Ŵ����� �ּҰ� ����
	void setEnemyMemoryLink(enemyManager* em) { _em = em; }

};

