#include "stdafx.h"
#include "omok.h"

omok::omok()
{
}

omok::~omok()
{
}

HRESULT omok::init()
{
	_turn = 0;
	_gameOver = false;

	int tempWidth = WINSIZEX / 20;
	int tempHeight = WINSIZEY / 20;

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			_loc[i][j].loc = NONE;
			_loc[i][j].x = (j + 1) * tempWidth;
			_loc[i][j].y = (i + 1) * tempHeight;
			_loc[i][j].rc = RectMakeCenter(_loc[i][j].x, _loc[i][j].y, 50, 50);
		}
	}

	return S_OK;
}

void omok::release()
{
}

void omok::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _gameOver == false)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (PtInRect(&_loc[i][j].rc, _ptMouse) && _loc[i][j].loc == NONE)
				{
					_loc[i][j].loc = (_turn % 2 == 0) ? BLACK : WHITE;
					if (_loc[i][j].loc == BLACK)
						IMAGEMANAGER->addImage("°ËÀºµ¹", "images/black.bmp", 50, 33, true, RGB(255, 0, 255));
					if (_loc[i][j].loc == WHITE)
						IMAGEMANAGER->addImage("Èòµ¹", "images/white.bmp", 50, 33, true, RGB(255, 0, 255));
					_turn++;
				}
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//°¡·Î
			if (_loc[i][j].loc == WHITE &&
				_loc[i][j + 1].loc == WHITE &&
				_loc[i][j + 2].loc == WHITE &&
				_loc[i][j + 3].loc == WHITE &&
				_loc[i][j + 4].loc == WHITE)
			{
				_gameOver = true;
				_wp = WP_WHITE;
			}

			//¼¼·Î
			if (_loc[i][j].loc == WHITE &&
				_loc[i + 1][j].loc == WHITE &&
				_loc[i + 2][j].loc == WHITE &&
				_loc[i + 3][j].loc == WHITE &&
				_loc[i + 4][j].loc == WHITE)
			{
				_gameOver = true;
				_wp = WP_WHITE;
			}

			//¿ì´ë°¢
			if (_loc[i][j].loc == WHITE &&
				_loc[i + 1][j + 1].loc == WHITE &&
				_loc[i + 2][j + 2].loc == WHITE &&
				_loc[i + 3][j + 3].loc == WHITE &&
				_loc[i + 4][j + 4].loc == WHITE)
			{
				_gameOver = true;
				_wp = WP_WHITE;
			}

			//ÁÂ´ë°¢
			if (i > 3 &&
				_loc[i][j].loc == WHITE &&
				_loc[i - 1][j + 1].loc == WHITE &&
				_loc[i - 2][j + 2].loc == WHITE &&
				_loc[i - 3][j + 3].loc == WHITE &&
				_loc[i - 4][j + 4].loc == WHITE)
			{
				_gameOver = true;
				_wp = WP_WHITE;
			}

			//°¡·Î
			if (_loc[i][j].loc == BLACK &&
				_loc[i][j + 1].loc == BLACK &&
				_loc[i][j + 2].loc == BLACK &&
				_loc[i][j + 3].loc == BLACK &&
				_loc[i][j + 4].loc == BLACK)
			{
				_gameOver = true;
				_wp = WP_BLACK;
			}

			//¼¼·Î
			if (_loc[i][j].loc == BLACK &&
				_loc[i + 1][j].loc == BLACK &&
				_loc[i + 2][j].loc == BLACK &&
				_loc[i + 3][j].loc == BLACK &&
				_loc[i + 4][j].loc == BLACK)
			{
				_gameOver = true;
				_wp = WP_BLACK;
			}

			//¿ì´ë°¢
			if (_loc[i][j].loc == BLACK &&
				_loc[i + 1][j + 1].loc == BLACK &&
				_loc[i + 2][j + 2].loc == BLACK &&
				_loc[i + 3][j + 3].loc == BLACK &&
				_loc[i + 4][j + 4].loc == BLACK)
			{
				_gameOver = true;
				_wp = WP_BLACK;
			}

			//ÁÂ´ë°¢
			if (i > 3 &&
				_loc[i][j].loc == BLACK &&
				_loc[i - 1][j + 1].loc == BLACK &&
				_loc[i - 2][j + 2].loc == BLACK &&
				_loc[i - 3][j + 3].loc == BLACK &&
				_loc[i - 4][j + 4].loc == BLACK)
			{
				_gameOver = true;
				_wp = WP_BLACK;
			}
		}
	}
}

void omok::render()
{
	char tempChar[128];
	if (_turn % 2 == 0)
		sprintf_s(tempChar, "Èæµ¹Â÷·Ê");
	if (_turn % 2 == 1)
		sprintf_s(tempChar, "¹éµ¹Â÷·Ê");
	if (_gameOver == true && _wp == WP_BLACK)
		sprintf_s(tempChar, "Èæµ¹½Â¸®");
	if (_gameOver == true && _wp == WP_WHITE)
		sprintf_s(tempChar, "¹éµ¹½Â¸®");
	SetTextAlign(getMemDC(), TA_CENTER);
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), WINSIZEX / 2, 10, tempChar, strlen(tempChar));
			
	for (int i = 0; i < 19; i++)
	{
		MoveToEx(getMemDC(), _loc[i][0].x, _loc[i][0].y, NULL);
		LineTo(getMemDC(), _loc[i][18].x, _loc[i][18].y);
		MoveToEx(getMemDC(), _loc[0][i].x, _loc[0][i].y, NULL);
		LineTo(getMemDC(), _loc[18][i].x, _loc[18][i].y);
	}

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (_loc[i][j].loc != NONE && _loc[i][j].loc != WHITE)
			{
				IMAGEMANAGER->render("°ËÀºµ¹", getMemDC(), _loc[i][j].rc.left, _loc[i][j].rc.top);
			}

			if (_loc[i][j].loc != NONE && _loc[i][j].loc != BLACK)
			{
				IMAGEMANAGER->render("Èòµ¹", getMemDC(), _loc[i][j].rc.left, _loc[i][j].rc.top);
			}
		}
	}


}
