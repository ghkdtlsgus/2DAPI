#pragma once
#include "gameNode.h"

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float speed;
	float angle;
	bool fire;
	int count;
};

//누구든 쓸수 잇음
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet() {};
	~bullet() {};

	HRESULT init(char* imageName,int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;
	int _bulletMax;

public:
	HRESULT init(float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();

	missile() {}
	~missile() {}
};

class missileM1 : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	
	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
	missileM1() {}
	~missileM1() {}
};