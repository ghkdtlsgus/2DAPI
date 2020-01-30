#include "stdafx.h"
#include "imgData.h"


HRESULT imgData::init()
{
	// ÀÌ¹ÌÁö Ãß°¡ 
	GDIPMANAGER->addImg("¹öÆ°", "img/button.png", 5, 6);
	GDIPMANAGER->addImg("Map1-1", "img/Map1/Map1-1.png");
	GDIPMANAGER->addImg("Map1-2", "img/Map1/Map1-2.png");
	GDIPMANAGER->addImg("Map1-3", "img/Map1/Map1-3.png");
	GDIPMANAGER->addImg("Map1-4", "img/Map1/Map1-4.png");
	GDIPMANAGER->addImg("Map1-5", "img/Map1/Map1-5.png");
	GDIPMANAGER->addImg("Sheep1-1", "img/Map1/Sheep1-1.png",14,4);
	GDIPMANAGER->addImg("Èò»ö", "images/Èò»ö.bmp");
	GDIPMANAGER->addImg("Map1-6", "img/Map1/Map1-6.png");
	GDIPMANAGER->addImg("Map1-7", "img/Map1/Map1-7.png");
	GDIPMANAGER->addImg("Map1-8", "img/Map1/Map1-8.png",15,1);
	GDIPMANAGER->addImg("Map1-9", "img/Map1/Map1-9.png");
	GDIPMANAGER->addImg("Map1-10", "img/Map1/Map1-10.png");
	GDIPMANAGER->addImg("Map1-11", "img/Map1/Map1-11.png");
	GDIPMANAGER->addImg("Map1-12", "img/Map1/Map1-12.png");
	GDIPMANAGER->addImg("Map1-Sun", "img/Map1/Map1-Sun.png");
	GDIPMANAGER->addImg("Map1-Water", "img/Map1/Map1-Water.png");
	GDIPMANAGER->addImg("Map1-Water-Alpha", "img/Map1/Map1-Water-Alpha.png"); 
	GDIPMANAGER->addImg("Map1-grass", "img/Map1/Map1-grass.png");
	return S_OK;
}

imgData::imgData()
{
}


imgData::~imgData()
{
}
