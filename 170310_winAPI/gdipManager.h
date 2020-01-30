#pragma once
#include "singletonBase.h"

struct gdipimage {
	Gdiplus::Image *gimg;
	int gx;
	int gy;
	float gwidth;
	float gheight;
};

class gdipManager : public singletonBase<gdipManager>
{
protected:
	typedef map<string, gdipimage*> mimgList;
	typedef map<string, gdipimage*>::iterator timgList;
	mimgList imgList;

public:
	gdipManager();
	~gdipManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//non-frame render
	void render(HDC hdc, string strKey, int x = 0, int y = 0);
	void renderimgsize(HDC hdc, string strKey, int height, int width, int x = 0, int y = 0);
	void rendersize(HDC hdc, string strKey,float size =0 ,int x = 0, int y = 0);
	void renderXFlip(HDC hdc, string strKey,float size = 0,int x = 0, int y = 0);
	void renderF(HDC hdc, string strKey, int frameX = 0, int frameY = 0, int x = 0, int y = 0);
	void renderFsize(HDC hdc, string strKey,float size = 0 ,int frameX = 0, int frameY = 0, int x = 0, int y = 0);
	void renderFXFlip(HDC hdc, string strKey, float size = 0, int frameX = 0, int frameY = 0, int x = 0, int y = 0);
	void renderFHorizontal(HDC hdc, string strKey, int frame = 0, int x = 0, int y = 0);
	void renderFVertical(HDC hdc, string strKey, int frame = 0, int x = 0, int y = 0);

	void renderR(HDC hdc, string strKey, float angle = 0.0f, int x = 0, int y = 0);

	void renderFR(HDC hdc, string strKey, int frameX = 0, int frameY = 0, float angle = 0.0f, int x = 0, int y = 0);
	void renderFRHorizontal(HDC hdc, string strKey, int frame = 0, float angle = 0.0f, int x = 0, int y = 0);
	void renderFRVertical(HDC hdc, string strKey, int frame = 0, float angle = 0.0f, int x = 0, int y = 0);

	gdipimage* findImg(string strKey);
	gdipimage* addImg(string strKey, const char *path, int x = 1, int y = 1);

	bool IsValid(Gdiplus::Image *img) const;
	bool delAll();
};

