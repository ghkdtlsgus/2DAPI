#pragma once
#include "gameNode.h"
// == 맵툴 헤더 == 
#include "Maptool.h"

//화면왼쪽
#define TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 8
//지형
enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

//오브젝트
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

//위치좌표
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//타일구조체
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

//이미지 타일 구조체
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
	// ＆맵툴 클래스 추가 
	Maptool* MaptoolC;
	////세이브,로드,지형,오브젝트,지우개
	//HWND m_btnSave;
	//HWND m_btnLoad;
	//HWND m_btnTerrainDraw;
	//HWND m_btnObjDraw;
	//HWND m_btnEraser;
	//
	//// 실험
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

	 //맵툴 셋팅
	 void maptoolSetup();
	 void setMap();
	 //숙제
	 void save();
	 void load(const char* MapKey);
	 //지형,오브젝트
	 TERRAIN terrainSelect(int frameX, int frameY);
	 OBJECT objSelect(int frameX, int frameY);
};

