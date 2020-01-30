#pragma once
#include "gameNode.h"

enum playerState
{
	PS_IDLE,
	PS_RUN
};

class player : public gameNode
{
private:
	image* _megaman;
	int _alpha;
	int _camera;
	int _count;
	int _index;
	bool _isLeft;
	playerState _ps;

public:
	player();
	~player();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

