#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;			//맵으로 만든 이미지 목록
	typedef map<string, image*>::iterator mapImageIter;	//맵으로 만든 이미지 목록의 반복자

private:
	mapImageList _mImageList;	//맵으로 구현된 이미지 목록

public:
	//이미지 매니져 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	//키값으로 빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//키값으로 이미지 파일 초기화(주 사용)
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//키값으로 프레임 이미지 파일로 초기화
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체삭제
	BOOL deleteAll();

	//===============================================
	//		## 일반렌더 ##
	//===============================================
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//===============================================
	//		## 알파렌더 ##
	//===============================================
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//===============================================
	//		## 프레임렌더 ##
	//===============================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//===============================================
	//		## 루프렌더 ##
	//===============================================
	//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	imageManager();
	~imageManager();
};

