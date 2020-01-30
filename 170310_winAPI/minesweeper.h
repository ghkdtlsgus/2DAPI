#pragma once
#include "gameNode.h"

#define WIDTH 10
#define HEIGHT 10
#define MINE 20

struct tagPuzzle
{
	RECT box;
	bool choise;
	int idNumber;
	bool purple;
	bool red;
	bool orange;
	bool yellow;
	bool green;
	bool blue;
};

struct tagLandmine
{
	RECT mine;
	bool stop;
	int idNumber;
};

class minesweeper : public gameNode
{
private:
	tagPuzzle _box[WIDTH][HEIGHT];
	tagPuzzle _shuffleBox[WIDTH * HEIGHT];
	tagLandmine _mine[MINE];
	HBRUSH _brush;
	int _downX, _downY;
	bool _win, _lose;
	char _winer[64];
	int _color;
	int _count;

public:
	minesweeper();
	~minesweeper();

	HRESULT init();
	void release();
	void update();
	void render();

	void mineCheck(int downX, int downY);

};

