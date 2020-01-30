#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);
	//���� Ŭ�� init 
	MaptoolC = new Maptool;
	MaptoolC->init();

	IMAGEMANAGER->addFrameImage("tilemap", "images/tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
	GDIPMANAGER->addImg("button", "images/tilemap.bmp", 5, 6);
	GDIPMANAGER->addImg("1", "images/tilemap.bmp");
	maptoolSetup();

	m_currentTile.x = 2;
	m_currentTile.y = 0;
	
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ���� ������ ���� ����� �� ����
	//init() ���� �����Ҵ� new ������ �̰����� SAFE_DELETE ����ϸ� ��
	SAFE_DELETE(MaptoolC);
}

void mainGame::update()
{
	gameNode::update();
	MaptoolC->update();

}

void mainGame::render()
{
	//����ۿ� �ѷ��ش�.(������ �׳� �Ѱ�)
	//HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	
	// ���� Ŭ�� render 
	MaptoolC->render();



	/*IMAGEMANAGER->render("tilemap", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth(), 0);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), m_tiles[i].rc.left, m_tiles[i].rc.top, m_tiles[i].terrainFrameX, m_tiles[i].terrainFrameY);

		if (m_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("tilemap",
			getMemDC(), m_tiles[i].rc.left, m_tiles[i].rc.top,
			m_tiles[i].objFrameX, m_tiles[i].objFrameY);
	}
*/
	// ======================================
	//              �� 
	// ======================================
	//Rectangle(getMemDC(), 0, 0, 1100, 700);
	//Rectangle(getMemDC(), 1120, 0, 1450, 700);
	//Rectangle(getMemDC(), 10, 710, 110, 760);
	//GDIPMANAGER->renderF(getMemDC(), "button", 0, 0, 0 ,0);
	//GDIPMANAGER->render(getMemDC(), "1",0,0);
	//===================================================
	//������� ������ hdc�� �׸���.(�̰͵� �� �Ѱ�!)
	this->getBackBuffer()->render(getHDC());
}

void mainGame::maptoolSetup()
{
	//H_edit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 1200, 720, 200, 30, _hWnd, HMENU(100), _hInstance, NULL);
	
	//// = hwnd = 
	//m_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	//m_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	//m_btnTerrainDraw = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	//m_btnObjDraw = CreateWindow("button", "OBJ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	//m_btnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);
	//// ����� ��ư
	//m_btnnextmap = CreateWindow("button", "NextMap", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 80, 20, _hWnd, HMENU(5), _hInstance, NULL);
	//m_btnbeforemap = CreateWindow("button", "BeforeMap", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80, 0, 80, 20, _hWnd, HMENU(6), _hInstance, NULL);
	//CreateWindow(NULL,NULL ,WS_CHILD | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_VISIBLE |
	//	WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 900,0,200,400, _hWnd, HMENU(7), _hInstance, NULL);
	////
	//ctrSelect = CTRL_TERRAINDRAW;
	//������ ����
	//for (int i = 0; i < SAMPLETILEY; i++)
	//{
	//	for (int j = 0; j < SAMPLETILEX; j++)
	//	{
	//		m_sampleTilep[i * SAMPLETILEX + j].terrainFrameX = j;
	//		m_sampleTilep[i * SAMPLETILEX + j].terrainFrameY = i;

	//		SetRect(&m_sampleTilep[i * SAMPLETILEX + j].rcTile,
	//			(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE,
	//			i * TILESIZE,
	//			(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
	//			i * TILESIZE + TILESIZE);
	//	}
	//}

	////���� ����
	//for (int i = 0; i < TILEX; i++)
	//{
	//	for (int j = 0; j < TILEY; j++)
	//	{
	//		SetRect(&m_tiles[i * TILEX + j].rc,
	//			j * TILESIZE,
	//			i * TILESIZE,
	//			j * TILESIZE + TILESIZE,
	//			i * TILESIZE + TILESIZE);
	//	}
	//}

	////ó���� ����ִ� Ÿ��
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	m_tiles[i].terrainFrameX = 2;
	//	m_tiles[i].terrainFrameY = 0;

	//	m_tiles[i].objFrameX = 0;
	//	m_tiles[i].objFrameY = 0;

	//	m_tiles[i].terrain = terrainSelect(m_tiles[i].terrainFrameX, m_tiles[i].terrainFrameY);
	//	m_tiles[i].obj = OBJ_NONE;
	//}
	//load();

	//   =====================================
	//      �� ���� �¾� �� 
	//   ====================================
	//   
	
}

void mainGame::setMap()
{
	////������ ����
	//for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	//{
	//	if (PtInRect(&m_sampleTilep[i].rcTile, _ptMouse))
	//	{
	//		m_currentTile.x = m_sampleTilep[i].terrainFrameX;
	//		m_currentTile.y = m_sampleTilep[i].terrainFrameY;
	//		break;
	//	}
	//}

	////���� ��
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (PtInRect(&m_tiles[i].rc, _ptMouse))
	//	{
	//		if (ctrSelect == CTRL_TERRAINDRAW)
	//		{
	//			m_tiles[i].terrainFrameX = m_currentTile.x;
	//			m_tiles[i].terrainFrameY = m_currentTile.y;

	//			m_tiles[i].terrain = terrainSelect(m_currentTile.x, m_currentTile.y);
	//		}

	//		else if (ctrSelect == CTRL_OBJDRAW)
	//		{
	//			m_tiles[i].objFrameX = m_currentTile.x;
	//			m_tiles[i].objFrameY = m_currentTile.y;
	//			
	//			m_tiles[i].obj = objSelect(m_currentTile.x, m_currentTile.y);
	//		}

	//		else if (ctrSelect == CTRL_ERASER)
	//		{
	//			m_tiles[i].objFrameX = 0;
	//			m_tiles[i].objFrameY = 0;

	//			//m_tiles[i].terrainFrameX = 19;
	//			//m_tiles[i].terrainFrameY = 7;

	//			m_tiles[i].obj = OBJ_NONE;
	//			m_tiles[i].terrain = TR_END;
	//		}
	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}

	//}

}

void mainGame::save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile("tileMap.map",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, m_tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, m_pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
}

void mainGame::load(const char* MapKey)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(MapKey,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, m_tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, m_pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

}

TERRAIN mainGame::terrainSelect(int frameX, int frameY)
{
	//�ø�Ʈ
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}

	//��
	else if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}

	//�ܵ�
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}

	//��
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	
	return TR_GRASS;
}

OBJECT mainGame::objSelect(int frameX, int frameY)
{
	//��ũ1
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}

	//��ũ2
	else if (frameX == 19 && frameY == 7)
	{
		return OBJ_TANK2;
	}
	//��� 1��¥��
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}

	//��� 3��¥��
	if (frameX == 17 && frameY == 2)
	{
		return OBJ_BLOCK2;
	}

	//�������
	if (frameX == 12 && frameY == 3)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCK1;
}

/*
void mainGame::collision()
{
	for(int i=0; i< _missileM1->getVBullet().size(); i++)
	{
		for(int j =0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if(IntersectRect(&rc, &_missileM1->getVBullet()[i].rc,
			&_em->getVBullet()[j]->getRect()))
			{
				_missileM1->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

*/