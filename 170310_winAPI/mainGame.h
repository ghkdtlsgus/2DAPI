#pragma once
#include "gameNode.h"
// == ���� ��� == 
#include "Maptool.h"

//ȭ�����
#define TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8
//����
enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_NONE
};

//��ġ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};

class mainGame : public gameNode
{
private:
	// ������ Ŭ���� �߰� 
	Maptool* MaptoolC;
	////���̺�,�ε�,����,������Ʈ,���찳
	//HWND m_btnSave;
	//HWND m_btnLoad;
	//HWND m_btnTerrainDraw;
	//HWND m_btnObjDraw;
	//HWND m_btnEraser;
	//
	//// ����
	//HWND m_btnnextmap;
	//HWND m_btnbeforemap;
	//HWND m_terrain;

	
		//
	tagCurrentTile m_currentTile;
	tagTile m_tiles[TILEX * TILEY];
	tagSampleTile m_sampleTilep[SAMPLETILEX * SAMPLETILEY];
	int m_pos[2];
public:
	mainGame();
	~mainGame();

	 HRESULT init();
	 void release();
	 void update();
	 void render();

	 //���� ����
	 void maptoolSetup();
	 void setMap();
	 //����
	 void save();
	 void load(const char* MapKey);
	 //����,������Ʈ
	 TERRAIN terrainSelect(int frameX, int frameY);
	 OBJECT objSelect(int frameX, int frameY);
};

