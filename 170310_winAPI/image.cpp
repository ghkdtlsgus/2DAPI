#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib")	//���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
//�ɹ� �̴ϼȶ������ �̹��� Ŭ���� �ɹ����� ���� �ٷ� �ʱ�ȭ �Ѵ�
image::image()
	:_imageInfo(NULL)
	, _fileName(NULL)
	, _isTrans(NULL)
	, _transColor(RGB(0, 0, 0))
	, _blendImage(NULL)
{
}

image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;


}
//�̹��� ���ҽ� �ʱ�ȭ(������)
HRESULT image::init(const DWORD resId, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resId;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//�̹��� ���Ϸ� �ҷ����°� �߿���
//�̹��� ���� �ʱ�ȭ
HRESULT image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� ��� �մٸ� ������ ���� ���� ��!!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�

	//�̹��� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / frameX / 2);
	_imageInfo->y = y - (height / frameY / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�� ��� AC_SRC_ALPHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� ����)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������

										//�̹��� ���� �����ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

//����Ű ����
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//������
void image::release()
{
	//�̹��� ������ ���� �ִٸ� ������(����) ���ٰ�
	if (_imageInfo)
	{
		//�̹�������
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hOBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//�����÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//����(���� ������ ��ġ�� �̹����� ����Ѵ�)
void image::render(HDC hdc)
{
	if (_isTrans) //���� ���ٰų�?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			0,						//����� ��ǥ ������ x
			0,						//����� ��ǥ ������ y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//���� �������� xy
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����Ű��
			_transColor);			//�����Ҷ� ������ ����(����Ÿ���� �����)
	}

	else//�����̹��� �״�� ��� �Ұų�?
	{
		//DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٰų�?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,						//����� ��ǥ ������ x
			destY,						//����� ��ǥ ������ y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//���� �������� xy
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����Ű��
			_transColor);			//�����Ҷ� ������ ����(����Ÿ���� �����)
	}
	else//�����̹��� �״�� ��� �Ұų�?
	{
		//DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //���� ���ٰų�?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//����� ����� DC
			destX,				//����� ��ǥ ������ x
			destY,				//����� ��ǥ ������ y
			sourWidth,			//����� �̹��� ����ũ��
			sourHeight,			//����� �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			sourX, sourY,		//���� �������� xy
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����Ű��
			_transColor);		//�����Ҷ� ������ ����(����Ÿ���� �����)
	}
	else//�����̹��� �״�� ��� �Ұų�?
	{
		//DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	//����(����Ÿ) ���� �� ���ĺ��� �Ұų�?
	if (_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׷��ش�.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc,
			destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ�� ������)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	//����(����Ÿ) ���� �� ���ĺ��� �Ұų�?
	if (_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׷��ش�.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc,
			destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ�� ������)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٰų�?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->frameWidth,	//����� �̹��� ����ũ��
			_imageInfo->frameHeight,//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, //���� �������� x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� �������� y
			_imageInfo->frameWidth,			//���� ���� ����ũ��
			_imageInfo->frameHeight,		//���� ���� ����Ű��
			_transColor);			//�����Ҷ� ������ ����(����Ÿ���� �����)
	}
	else//�����̹��� �״�� ��� �Ұų�?
	{
		//DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //���� ���ٰų�?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->frameWidth,	//����� �̹��� ����ũ��
			_imageInfo->frameHeight,//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, //���� �������� x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� �������� y
			_imageInfo->frameWidth,			//���� ���� ����ũ��
			_imageInfo->frameHeight,		//���� ���� ����Ű��
			_transColor);			//�����Ҷ� ������ ����(����Ÿ���� �����)
	}
	else//�����̹��� �״�� ��� �Ұų�?
	{
		//DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	alphaRender(hdc, destX, destY,
		currentFrameX * _imageInfo->frameWidth,
		currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight, alpha);
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ� ���ٸ�(ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �� ��ŭ ����Ʈ ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׸���
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}

}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ� ���ٸ�(ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �� ��ŭ ����Ʈ ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׸���
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}

}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
