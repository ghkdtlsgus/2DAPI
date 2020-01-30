#pragma once
#include "gameNode.h"

enum Loc
{
	NONE,
	BLACK,
	WHITE
};

enum winPlayer
{
	WP_BLACK,
	WP_WHITE
};

struct tagLoc
{
	Loc loc;
	RECT rc;
	float x, y;
};

class omok : public gameNode
{
private:
	tagLoc _loc[19][19];
	bool _gameOver;
	winPlayer _wp;
	int _turn;

public:
	omok();
	~omok();

	HRESULT init();
	void release();
	void update();
	void render();
};

