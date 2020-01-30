#pragma once
#include "gameNode.h"
#include "progressBar.h"

//�ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,	//�� ��Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,	//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,	//�Ϲ� �̹���(��ġ ��ǥ ����)
	LOAD_KIND_FRAMEIMAGE_0,	//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,	//������ �̹���(��ġ �� ����)
	LOAD_KIND_SOUND,
	LOAD_KIND_ENd
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;		//�̹��� Ű��
	const char* fileName;	//���� �̸�
	int x, y;				//��ġ ��ǥ
	int width, height;		//���� ���� ũ��
	int frameX, frameY;		
	bool trans;		//��� ���ٰ���?
	COLORREF transColor;	//���� �÷�Ű
};

class loadItem
{
private:
	LOAD_KIND m_kind;
	tagImageResource m_imageResource;

public:
	loadItem() {}
	~loadItem() {}

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	HRESULT initForImage(string keyName, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));
	HRESULT initForImage(string keyName, const char* fileName,float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�ε� ������ ���� ��������
	LOAD_KIND getLoadingKind() { return m_kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource() { return m_imageResource; }
};


class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;

	arrLoadItem m_vLoadItem;

	//�ε�ȭ�鿡�� ����� �̹��� �� �ε���
	image* m_backGround;
	progressBar* m_loadingBar;	//�ε� ȭ�鿡�� ����� �ε���
	int m_currentGauge;	//�ε��� ������

public:
	loading() {};
	~loading() {};

	HRESULT init();
	void release();
	void update();
	void render();

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	void loadImage(string keyName, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName,float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�ε� �Ϸ� ���?(�ε� �Ϸ� �� �� ����)
	BOOL loadingDone();

	//�ε� ������ ���� ��������
	vector<loadItem*> getLoadItem() { return m_vLoadItem; }
};

