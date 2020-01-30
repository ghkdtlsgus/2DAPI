#pragma once
#include "gameNode.h"
#include "Rcdata.h"
#include "Pagedata.h"
#include "FrameRender.h"
using namespace std;

// �ʱ��� 0 ~ 2000 
//�ڽ��� x 1100 y 700      max y 1200
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
	// Rcdata Ŭ���� 
	Rcdata* RcdataC;
	// Page Ŭ����
	Pagedata* PagedataC;
	// �����ӷ��� �� ���
	FrameRender FrameRenderC;
	// ===========
	RECT Rc[6];
	tagMap m_tagMap[Max];
	//����ü �ʱ�ȭ ���� 
	int RcNum;
	// ���� Ÿ��
	Type Typebtn;
	// �浹üũ RC 
	RECT Check_img_rc[100];
	
	//���̸� ���� ����
	//char* MapName;
	TCHAR MapName[256];
	HWND H_edit;

	//���ڿ�
	char strText[128];

	//���� ��� ���ֳ�
	int check_isdata;
public:
	// =============
	//  �⺻���� 
	HRESULT init();
	void release();
	void update();
	void render();
	// ==============
	void Save(char* MapKey);
	void Load(char* MapKey);
	void RightCollision();
	// �ʿ� �̹��� �ֱ� 
	void Applyimg();
	void Maptoolsetup();
	// ��ư Ŭ��
	void BtnClick();
	//�̿� ���÷���
	float zoomplus();
	//�̿� �ܸ��̳ʽ�
	float zoommius();
	//���̺� �ε� ptinrect
	void Save_Load();
	//�������� �ǵ�����
	void PrevValue();
	//Xflip
	void Xflip();
	//Yflip
	void Yflip();
//���� ȭ���� �ʿ� ���� ���� 	
public:
	//��ũ�� X��ǥ, ���� �� ��ǥ
	double m_Screen_X;
	//��ũ�� Y��ǥ, ���� �� ��ǥ
	double m_Screen_Y;
private:
	void Scroll();
	void DrawScreenMap();
public:
	Maptool();
	~Maptool();
};

