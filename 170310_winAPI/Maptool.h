#pragma once
#include "gameNode.h"
#include "Rcdata.h"
#include "Pagedata.h"
#include "FrameRender.h"
using namespace std;

// 맵길이 0 ~ 2000 
//박스안 x 1100 y 700      max y 1200
#define Max 100
#define ScreenX_MAX 1100
#define ScreenY_MAX 700
enum Type
{
	Notting,
	Object,
	Terrain
};

struct tagMap
{
	bool isdata;
	bool isFrameimg;
	int Frame_X;
	int Frame_Y;
	int Frame_Max_X;
	int Frame_Max_Y;
	int Count;
	bool isXflip;
	bool isYflip;
	Type type;
	RECT rc;
	string mapkey;
	float size;
};

class Maptool : public gameNode
{
private:
	int ii;
	// Rcdata 클래스 
	Rcdata* RcdataC;
	// Page 클래스
	Pagedata* PagedataC;
	// 프레임렌더 값 계산
	FrameRender FrameRenderC;
	// ===========
	RECT Rc[6];
	tagMap m_tagMap[Max];
	//구조체 초기화 변수 
	int RcNum;
	// 현재 타입
	Type Typebtn;
	// 충돌체크 RC 
	RECT Check_img_rc[100];
	
	//맵이름 담을 변수
	//char* MapName;
	TCHAR MapName[256];
	HWND H_edit;

	//문자열
	char strText[128];

	//현재 몇개가 들어가있나
	int check_isdata;
public:
	// =============
	//  기본설정 
	HRESULT init();
	void release();
	void update();
	void render();
	// ==============
	void Save(char* MapKey);
	void Load(char* MapKey);
	void RightCollision();
	// 맵에 이미지 넣기 
	void Applyimg();
	void Maptoolsetup();
	// 버튼 클릭
	void BtnClick();
	//미완 줌플러스
	float zoomplus();
	//미완 줌마이너스
	float zoommius();
	//세이브 로드 ptinrect
	void Save_Load();
	//이전으로 되돌리기
	void PrevValue();
	//Xflip
	void Xflip();
	//Yflip
	void Yflip();
//맵툴 화면의 맵에 대한 정보 	
public:
	//스크린 X좌표, 실제 맵 좌표
	double m_Screen_X;
	//스크린 Y좌표, 실제 맵 좌표
	double m_Screen_Y;
private:
	void Scroll();
	void DrawScreenMap();
public:
	Maptool();
	~Maptool();
};

