#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//상호참조용 적 매니져 클래스 전방선언
class enemyManager;

struct tagPlayer
{
	image* img;
	float speed;
};

class rocket : public gameNode
{
private:
	tagPlayer _player;	//플레이어 구조체
	missile* _missile;	//미사일 클래스
	missileM1* _missileM1;

	progressBar* _hpBar;
	float _maxHP;
	float _currentHP;

	enemyManager* _em;	//에너미 매니져 클래스 선언만 하기

public:
	rocket();
	~rocket();

	HRESULT init();
	void release();
	void update();
	void render();

	//미사일 삭제
	void removeMissile(int arrNum);
	//충돌함수
	void collsion();
	//피통 깍기 함수
	void hitDamage(float damage);

	//로켓 이미지 가져오기
	image* getRocketImage() { return _player.img; }

	//미사일 M1 가져오기
	missileM1* getMissile() { return _missileM1; }

	//상호참조하기 위해 적매니져의 주소값 공유
	void setEnemyMemoryLink(enemyManager* em) { _em = em; }

};

