#include "stdafx.h"
#include "Rcdata.h"




void Rcdata::init()
{
	_saveinfo.isinfo = false;
	_info.isinfo = true;
	_info.isFrameimg = false;
	_info.isXflip = false;
	_info.isYflip = false;
	_info.Frame_Max_X = NULL;
	_info.Frame_Max_Y = NULL;
	_info.Size = 1.0f; // 렌더 사이즈 
	// 1번째 값 
	_info.RC = { 1150,30,1400,330 };
	_info.RCimg = { 251,333,0,0 };
	_info.Key = "Map1-1";
	_vInfo.push_back(_info);
	// 2번째 값
	_info.RC = { 1120,340,1450,626 };
	_info.RCimg = { 394,291,0,0 };
	_info.Key = "Map1-2";
	_vInfo.push_back(_info);
	_vvInfo.push_back(_vInfo); // 0번쩨 페이지

	_vInfo.clear();
	// 1번째 페이지 시작
	_info.RC = { 1120,30,1120 + 440,30 + 261 };
	_info.RCimg = { 436,261,0,0 };
	_info.Key = "Map1-3";
	_vInfo.push_back(_info);
	_info.RC = { 1200,261, 1300 , 450 };
	_info.RCimg = { 199,371,0,0 };
	_info.Key = "Map1-4";
	_vInfo.push_back(_info);
	_info.RC = { 1200,451,1380,662 };
	_info.RCimg = { 256,305,0,0 };
	_info.Key = "Map1-5";
	_vInfo.push_back(_info);
	_vvInfo.push_back(_vInfo);
	//2번째 페이지 시작 
	_vInfo.clear();

	_info.isFrameimg = false;
	_info.RC = { 1200,100,1200 + 293,100 + 43 };
	_info.RCimg = { 293,43,0,0 };
	_info.Key = "Map1-6";
	_info.Frame_Max_X = NULL;
	_info.Frame_Max_Y = NULL;
	_vInfo.push_back(_info);

	_info.RC = { 1250,150,1250 + 111,150 + 17 };
	_info.RCimg = { 111,17,0,0 };
	_info.Key = "Map1-7";
	_vInfo.push_back(_info);

	_info.RC = { 1150,200,1150 + 302,200 + 75 };
	_info.RCimg = { 302,75,0,0 };
	_info.Key = "Map1-9";
	_vInfo.push_back(_info);

	_info.RC = { 1150,300,1150 + 297,300 + 69 };
	_info.RCimg = { 297,69,0,0 };
	_info.Key = "Map1-10";
	_vInfo.push_back(_info);

	_info.RC = { 1150,380 , 1150 + 341,380 + 64 };
	_info.RCimg = { 341,64,0,0 };
	_info.Key = "Map1-11";
	_vInfo.push_back(_info);

	_info.RC = { 1200, 450 , 1200 + 16 , 450 + 51 };
	_info.RCimg = { 16, 51 , 0 ,0 };
	_info.Key = "Map1-12";
	_vInfo.push_back(_info);

	_info.RC = { 1200, 510 , 1200 + 51 * 3,510 + 51 * 3 };
	_info.Size = 0.3f;
	_info.RCimg = { 51 * 3,51 * 3,0,0 };
	_info.Key = "Map1-Sun";
	_vInfo.push_back(_info);

	_info.Size = 1.0f;
	_info.isFrameimg = true;
	_info.RC = { 1250,50,1290,80 };
	_info.RCimg = { 20,15,0,0 };
	_info.Key = "Sheep1-1";
	_info.Frame_Max_X = 13;
	_info.Frame_Max_Y = 3;
	_vInfo.push_back(_info);

	_info.RC = { 1250,180,1250 + 54,190 };
	_info.RCimg = { 54,5,0,0 };
	_info.Key = "Map1-8";
	_info.Frame_Max_X = 14;
	_info.Frame_Max_Y = 0;
	_vInfo.push_back(_info);

	_vvInfo.push_back(_vInfo);
	// 3번
	_vInfo.clear();

	_info.isFrameimg = false;
	_info.RC = { 1200,50, 1200 + 200,50 + 100 };
	_info.Key = "Map1-Water";
	_info.RCimg = { 200,100,0,0 };
	_vInfo.push_back(_info);
	

	_info.RC = { 1200, 200, 1200 + 200, 200 + 200 };
	_info.Key = "Map1-grass";
	_info.RCimg = { 200,200,0,0 };
	_vInfo.push_back(_info);
	_vvInfo.push_back(_vInfo);


}

Rcdata::Rcdata()
{
}


Rcdata::~Rcdata()
{
}
