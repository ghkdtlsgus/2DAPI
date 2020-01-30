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
	for (int y = 0; y < HEIGHT; y++)//����
	{
		for (int x = 0; x < WIDTH; x++) //����
		{
			//������
			_box[x][y].box = RectMake(x * WINSIZEX / WIDTH, y * WINSIZEY / HEIGHT, WINSIZEX / WIDTH, WINSIZEY / HEIGHT);
			_box[x][y].idNumber = x + (y * WIDTH);	//�����ǹ�ȣ
			_box[x][y].choise = false;	//����Ŭ������

			_shuffleBox[i].box = _box[x][y].box;
			_shuffleBox[i].idNumber = _box[x][y].idNumber;
			i++;

			//������
			_box[x][y].purple = false;
			_box[x][y].red = false;
			_box[x][y].orange = false;
			_box[x][y].yellow = false;
			_box[x][y].green = false;
			_box[x][y].blue = false;
		}
	}

	//����
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

	//�������ڹ�ġ
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
					_count++;	//���������� ������Ű�� ����
					_downX = x;
					_downY = y;

					mineCheck(_downX, _downY);

					//�˻����� ���� ��
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
	//����� �̹��� �Ѹ���..
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
				if (_mine[i].stop == true) // ���� ���
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
					if (_box[x][y].purple == true) // ����
					{
						_brush = CreateSolidBrush(RGB(128, 0, 255));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}

					if (_box[x][y].red == true) // ����
					{
						_brush = CreateSolidBrush(RGB(255, 0, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].orange == true) // ��Ȳ
					{
						_brush = CreateSolidBrush(RGB(255, 128, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].yellow == true) // ���
					{
						_brush = CreateSolidBrush(RGB(255, 255, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].green == true) // �ʷ�
					{
						_brush = CreateSolidBrush(RGB(0, 255, 0));
						_brush = (HBRUSH)SelectObject(getMemDC(), _brush);
						Rectangle(getMemDC(), _box[x][y].box.left, _box[x][y].box.top, _box[x][y].box.right, _box[x][y].box.bottom);
						DeleteObject(_brush);
						break;
					}
					if (_box[x][y].blue == true) // �Ķ�
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

	if (_lose == true) // ���н� ���
	{
		sprintf_s(_winer, "����");
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _winer, strlen(_winer));
	}

	if (_win == true) // ������ ���
	{
		sprintf_s(_winer, "��� ���ڸ� ã�ҽ��ϴ�.");
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
			//��ü�����ְ� ������ 
			/*for (int i = 0; i < MINE; i++)
			{
				_mine[i].stop = true;
				_lose = true;
			}*/
		}

		//���ڸ� ���� ������ �ְ� 8�� �˻�
		else
		{
			//���ʸ𼭸�
			if (downX == 0 && downY == 0)
			{
				//������ �Ʒ�
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}
			//���ʾƷ�(�𼭸�)
			else if (downX == 0 && downY == HEIGHT - 1)
			{
				//������ ��
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//��������(�𼭸�)
			else if (downX == WIDTH - 1 && downY == 0)
			{
				//���ʾƷ�
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//�����ʾƷ�(�𼭸�)
			else if (downX == WIDTH - 1 && downY == HEIGHT - 1)
			{
				//���� ��
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//���ʸ�
			else if (downX == 0)
			{
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ ��
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ �Ʒ�
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//�����ʸ�
			else if (downX == WIDTH - 1)
			{
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���� ��
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���� �Ʒ�
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//����
			else if (downY == 0)
			{
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���� �Ʒ�
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ �Ʒ�
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
			}

			//�Ʒ���
			else if (downY == HEIGHT - 1)
			{
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���� ��
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ ��
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
			}
			else
			{
				//����
				_color += (_box[downX - 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���� ��
				_color += (_box[downX - 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//��
				_color += (_box[downX][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ ��
				_color += (_box[downX + 1][downY - 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������
				_color += (_box[downX + 1][downY].idNumber == _mine[i].idNumber) ? 1 : 0;
				//������ �Ʒ�
				_color += (_box[downX + 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//�Ʒ�
				_color += (_box[downX][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;
				//���ʾƷ�
				_color += (_box[downX - 1][downY + 1].idNumber == _mine[i].idNumber) ? 1 : 0;

			}
		}
	}

	if (_count == HEIGHT * WIDTH - MINE) _win = true;	//����
}
