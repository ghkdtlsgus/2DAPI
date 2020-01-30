#include "stdafx.h"
#include "Pagedata.h"


HRESULT Pagedata::init()
{
	Page = 0;
	imgDataC = new imgData;
	imgDataC->init();
	SAFE_DELETE(imgDataC);
	return S_OK;
}

void Pagedata::Render()
{
	//오른쪽 칸 -> 오브젝트 
	if (Page == 0)
	{
		GDIPMANAGER->render(getMemDC(), "Map1-1", 1150, 0); // 333
		GDIPMANAGER->render(getMemDC(), "Map1-2", 1120, 333); 
	}
	else if (Page == 1)
	{
		GDIPMANAGER->render(getMemDC(), "Map1-3", 1120, 0); //261
		GDIPMANAGER->rendersize(getMemDC(), "Map1-4", 0.5f,1200, 261); // 371  / 186
		GDIPMANAGER->rendersize(getMemDC(), "Map1-5", 0.7f, 1200, 261 + 186); // 305
	}
	else if (Page == 2)
	{
		GDIPMANAGER->renderFsize(getMemDC(), "Sheep1-1", 2.0, 0, 0, 1250, 50);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-6", 0.5f, 1200, 100);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-7", 1.0f, 1250, 150);
		GDIPMANAGER->renderFsize(getMemDC(), "Map1-8", 2.0f, 0, 0, 1250, 180);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-9", 1.0f, 1150, 200);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-10", 1.0f, 1150, 300); //69
		GDIPMANAGER->rendersize(getMemDC(), "Map1-11", 1.0f, 1150, 380); //64
		GDIPMANAGER->rendersize(getMemDC(), "Map1-12", 1.0f, 1200, 450);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-Sun", 0.3f, 1200, 510);
	}
	else if (Page == 3)
	{
		GDIPMANAGER->rendersize(getMemDC(), "Map1-Water", 1.0f, 1200, 50);
		GDIPMANAGER->rendersize(getMemDC(), "Map1-grass", 1.0f, 1200, 200);
	}
	// 버튼  //Rectangle(getMemDC(), 1120, 0, 1180, 25);
	GDIPMANAGER->renderF(getMemDC(), "버튼", 1, 0, 1120, 0); // Next 
	GDIPMANAGER->renderF(getMemDC(), "버튼", 0, 0, 1180, 0); // Prev
}

Pagedata::Pagedata()
{
}


Pagedata::~Pagedata()
{
}
