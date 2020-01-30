#include "stdafx.h"
#include "minesweeper.h"

minesweeper::minesweeper()
{
}

minesweeper::~minesweeper()
{
}

HRESULT minesweeper::init()
{
	int i = 0;
	for (int y = 0; y < HEIGHT; y++)//세로
	{
		for (int x = 0; x < WIDTH; x++) //가로
		{
			//지뢰판
			_box[x][y].box = RectMake(x * WINSIZEX / WIDTH, y * WINSIZEY / HEIGHT, WINSIZEX / WIDTH, WINSIZEY / HEIGHT);
			_box[x][y].idNumber = x + (y * WIDTH);	//지뢰판번호
			_box[x][y].choise = false;	//이중클릭방지

			_shuffleBox[i].box = _box[x][y].box;
			_shuffleBox[i].idNumber = _box[x][y].idNumber;
			i++;

			//색셋팅
			_box[x][y].purple = false;
			_box[x][y].red = false;
			_box[x][y].orange = false;
			_box[x][y].yellow = false;
			_box[x][y].green = false;
			_box[x][y].blue = false;
		}
	}

	//셔플
	for (int i = 0; i < 1000; i++)
	{
		int dest, sour, tempNum;
		RECT temp;
		dest = RND->getFromIntTo(0, (WIDTH * HEIGHT) - 1);
		sour = RND->getFromIntTo(0, (WIDTH * HEIGHT) - 1);

		temp = _shuffleBox[dest].box;
		_shuffleBox[dest].box = _shuffleBox[sour].box;
		_shuffleBox[sour].box = temp;

		tempNum = _shuffleBox[dest].idNumber;
		_shuffleBox[dest].idNumber = _shuffleBox[sour].idNumber;
		_shuffleBox[sour].idNumber = tempNum;
	}

	//랜덤지뢰배치
	for (int i = 0; i < MINE; i++)
	{
		_mine[i].mine = _shuffleBox[i].box;
		_mine[i].idNumber = _shuffleBox[i].idNumber;
		_mine[i].stop = false;
	}

	_win = false;
	_lose = false;

	return S_OK;
}

void minesweeper::release()
{
}

void minesweeper::update()
{
	_color = 0;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _lose == false && _win == false)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (PtInRect(&_box[x][y].box, _ptMouse) && _box[x][y].choise == false)
				{
					_box[x][y].choise = true;
					_count++;	//성공조건을 만족시키기 위해
					_downX = x;
					_downY = y;

					mineCheck(_downX, _downY);

					//검사결과에 따른 색
					if (_color >= 5)  _box[x][y].purple = true;
					if (_color == 4)  _box[x][y].red = true;
					if (_color == 3)  _box[x][y].orange = true;
					if (_color == 2)  _box[x][y].yellow = true;
					if (_color == 1)  _box[x][y].green = true;
					if (_color == 0)  _box[x][y].blue = true;
				}
			}
		}
	}
}

void minesweeper::render()
{
	//출력할 이미지 뿌리고..
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			_brush = CreateSolidBrush(RGB(255, 255, 255));
			_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
			Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
			DeleteObject(_brush);

			for (int i = 0; i < MINE; i++)
			{
				if (_mine[i].stop == true) // 지뢰 출력
				{
					_brush = CreateSolidBrush(RGB(255, 255, 255));
					_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
					Rectangle(getMemDC(), _mine[i].mine.left, _mine[i].mine.top, _mine[i].mine.right, _mine[i].mine.bottom);
					DeleteObject(_brush);
					_brush = CreateSolidBrush(RGB(0, 0, 0));
					_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
					Ellipse(getMemDC(), _mine[i].mine.left, _mine[i].mine.top, _mine[i].mine.right, _mine[i].mine.bottom);
					DeleteObject(_brush);
				}

				if (_box[x][y].choise == true)
				{
					if (_box[x][y].purple == true) // 보라
					{
						_brush = CreateSolidBrush(RGB(128, 0, 255));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}

					if (_box[x][y].red == true) // 빨강
					{
						_brush = CreateSolidBrush(RGB(255, 0, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].orange == true) // 주황
					{
						_brush = CreateSolidBrush(RGB(255, 128, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].yellow == true) // 노랑
					{
						_brush = CreateSolidBrush(RGB(255, 255, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].green == true) // 초록
					{
						_brush = CreateSolidBrush(RGB(0, 255, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].blue == true) // 파랑
					{
						_brush = CreateSolidBrush(RGB(0, 0, 255));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
				}
			}
		}
	}

	if (_lose == true) // 실패시 출력
	{
		sprintf_s(_winer, "실패");
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _winer, strlen(_winer));
	}

	if (_win == true) // 성공시 출력
	{
		sprintf_s(_winer, "모든 지뢰를 찾았습니다.");
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _winer, strlen(_winer));
	}

}

void minesweeper::mineCheck(int downX, int downY)
{
	for (int i = 0; i < MINE; i++)
	{
		if (_box[downX][downY].idNumber == _mine[i].idNumber)
		{
			_mine[i].stop = true;
			_lose = true;
			break;
			//전체보여주고 싶을때 
			/*for (int i = 0; i < MINE; i++)
			{
				_mine[i].stop = true;
				_lose = true;
			}*/
		}

		//지뢰를 밟지 않으면 주견 8곳 검사
		else
		{
			//왼쪽모서리
			if (downX == 0 && downY == 0)
			{
				//오른쪽 아래
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}
			//왼쪽아래(모서리)
			else if (downX == 0 && downY == HEIGHT - 1)
			{
				//오른쪽 위
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//오른쪽위(모서리)
			else if (downX == WIDTH - 1 && downY == 0)
			{
				//왼쪽아래
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//오른쪽아래(모서리)
			else if (downX == WIDTH - 1 && downY == HEIGHT - 1)
			{
				//왼쪽 위
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//왼쪽면
			else if (downX == 0)
			{
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 위
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 아래
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//오른쪽면
			else if (downX == WIDTH - 1)
			{
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽 위
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽 아래
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//윗면
			else if (downY == 0)
			{
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽 아래
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 아래
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//아랫면
			else if (downY == HEIGHT - 1)
			{
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽 위
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 위
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
			}
			else
			{
				//왼쪽
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽 위
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//위
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 위
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//오른쪽 아래
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//아래
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//왼쪽아래
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;

			}
		}
	}

	if (_count == HEIGHT * WIDTH - MINE) _win = true;	//성공
}
