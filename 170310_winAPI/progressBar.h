#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;	//체력바 렉트
	int _x, _y;			//체력바 좌표
	int _width;			//체력바 가로길이(이걸로 조정)

	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressbarBack;	//체력바 뒤 이미지
public:
	progressBar();
	~progressBar();

	//체력바 초기화(앞이미지, 백이미지, x,y, 가로길이, 세로길이)
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	//프로그래스바 게이지 셋팅(초기화 후 꼭 해줄것!)
	void setGauge(float currnetGauge, float maxGauge);

	//프로그래스바 위치 셋팅
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	//체력바 렉트 가져오기
	RECT getRect() { return _rcProgress; }
};

