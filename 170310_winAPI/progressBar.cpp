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
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressbarBack = new image;
	_progressbarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	//���� ���� �ʱ�ȭ
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
	//���α׷����� ���̹���(����� �ʿ䰡 ����)
	_progressbarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressbarBack->getWidth(), _progressbarBack->getHeight());
	//���α׷����� ����Ʈ �̹���(���α��̰� ���� �Ǿ�� �Ѵ�.)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressbarBack->getHeight());
}

void progressBar::setGauge(float currnetGauge, float maxGauge)
{
	_width = (currnetGauge / maxGauge) * _progressbarBack->getWidth();
}
