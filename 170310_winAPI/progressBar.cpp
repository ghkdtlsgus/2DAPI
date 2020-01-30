#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;

	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//체력바 이미지 초기화
	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressbarBack = new image;
	_progressbarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	//가로 길이 초기화
	_width = _progressBarFront->getWidth();


	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressbarBack);
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x + _progressbarBack->getWidth() / 2,
		_y + _progressbarBack->getHeight() / 2,
		_progressbarBack->getWidth(), _progressbarBack->getHeight()
	);
}

void progressBar::render()
{
	//프로그래스바 뺵이미지(변경될 필요가 없다)
	_progressbarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressbarBack->getWidth(), _progressbarBack->getHeight());
	//프로그래스바 프론트 이미지(가로길이가 변경 되어야 한다.)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressbarBack->getHeight());
}

void progressBar::setGauge(float currnetGauge, float maxGauge)
{
	_width = (currnetGauge / maxGauge) * _progressbarBack->getWidth();
}
