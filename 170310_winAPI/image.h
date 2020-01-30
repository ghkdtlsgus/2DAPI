#pragma once
#include "animation.h"
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ� �ε�
		LOAD_FILE,				//���Ϸε�
		LOAD_EMPTY,				//�� ��Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//���ҽ�ID
		HDC			hMemDC;			//�޸� DC
		HBITMAP		hBit;			//��Ʈ��
		HBITMAP		hOBit;			//�õ� ��Ʈ��
		float		x;				//�̹��� x��ǥ
		float		y;				//�̹��� y��ǥ
		int			width;			//�̹��� ����ũ��
		int			height;			//�̹��� ����ũ��
		int			currentFrameX;	//���� ������ X
		int			currentFrameY;	//���� ������ Y
		int			maxFrameX;		//�ִ� X ������ ����
		int			maxFrameY;		//�ִ� Y ������ ����
		int			frameWidth;		//1������ ���α���
		int			frameHeight;	//1������ ���α���
		BYTE		loadType;		//�ε� Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO _imageInfo;	//�̹��� ����
	CHAR* _fileName;			//�̹��� �̸�
	BOOL _isTrans;				//���� ���ٰų�?(����Ÿ)
	COLORREF _transColor;		//���� ���� RGB(����Ÿ = RGB(255,0,255))

	BLENDFUNCTION _blendFunc;	//���ĺ����带 ���� ����
	LPIMAGE_INFO _blendImage;	//���ĺ����带 ����ϱ� ���� �̹��� ����
public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ(������)
	HRESULT init(const DWORD resId, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//���ĺ����� �ʱ�ȭ
	HRESULT initForAlphaBlend();

	//����Ű ����
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//������
	void release();

	//����(���� ������ ��ġ�� �̹����� ����Ѵ�)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���ķ���
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//��������(hdc,������ų����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//�ִϸ��̼� ����
	void aniRender(HDC hdc, int destX, int destY, animation* ani);


	//�ζ��� �Լ��� - ���� ����
	//DC ���´�
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//�̹��� x��ǥ ���(get)
	inline float getX() { return _imageInfo->x; }
	//�̹��� x��ǥ ����(set)
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� y��ǥ ���(get)
	inline float getY() { return _imageInfo->y; }
	//�̹��� y��ǥ ����(set)
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ ����
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//���� ũ�� ���
	inline int getWidth() { return _imageInfo->width; }
	//���� ũ�� ���
	inline int getHeight() { return _imageInfo->height; }

	//�ٿ���ڽ�(�浹��)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//������ X ����
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ Y ����
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1������ ���� ���� ũ��
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//�ƽ� ������ x,y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }
};
