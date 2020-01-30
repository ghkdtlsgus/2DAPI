#pragma once
#include "image.h"

//백버퍼 이미지를 스태틱으로 변경
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

//맵툴에서 사용할 컨트롤 이넘문
enum CTRL
{
	CTRL_H_edit = 100,  // 텍스트창 엔터  
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();



	//백버퍼 얻어오기
	image* getBackBuffer() { return _backBuffer; }
	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

