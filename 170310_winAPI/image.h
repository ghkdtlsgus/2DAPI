#pragma once
#include "animation.h"
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//리소스 로딩
		LOAD_FILE,				//파일로딩
		LOAD_EMPTY,				//빈 비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//리소스ID
		HDC			hMemDC;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드 비트맵
		float		x;				//이미지 x좌표
		float		y;				//이미지 y좌표
		int			width;			//이미지 가로크기
		int			height;			//이미지 세로크기
		int			currentFrameX;	//현재 프레임 X
		int			currentFrameY;	//현재 프레임 Y
		int			maxFrameX;		//최대 X 프레임 갯수
		int			maxFrameY;		//최대 Y 프레임 갯수
		int			frameWidth;		//1프레임 가로길이
		int			frameHeight;	//1프레임 세로길이
		BYTE		loadType;		//로드 타입

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
	LPIMAGE_INFO _imageInfo;	//이미지 정보
	CHAR* _fileName;			//이미지 이름
	BOOL _isTrans;				//배경색 없앨거냐?(마젠타)
	COLORREF _transColor;		//배경색 없앨 RGB(마젠타 = RGB(255,0,255))

	BLENDFUNCTION _blendFunc;	//알파블랜드를 위한 정보
	LPIMAGE_INFO _blendImage;	//알파블랜드를 사용하기 위한 이미지 정보
public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화(사용안함)
	HRESULT init(const DWORD resId, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	//이미지 파일 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//알파블랜드 초기화
	HRESULT initForAlphaBlend();

	//투명키 셋팅
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//릴리즈
	void release();

	//랜더(내가 지정한 위치에 이미지를 출력한다)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파렌더
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//루프렌더(hdc,루프시킬영역, x오프셋, y오프셋)
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//애니메이션 렌더
	void aniRender(HDC hdc, int destX, int destY, animation* ani);


	//인라인 함수들 - 겟터 셋터
	//DC 얻어온다
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//이미지 x좌표 얻기(get)
	inline float getX() { return _imageInfo->x; }
	//이미지 x좌표 설정(set)
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 y좌표 얻기(get)
	inline float getY() { return _imageInfo->y; }
	//이미지 y좌표 설정(set)
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터 좌표 셋팅
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//가로 크기 얻기
	inline int getWidth() { return _imageInfo->width; }
	//세로 크기 얻기
	inline int getHeight() { return _imageInfo->height; }

	//바운딩박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//프레임 X 셋팅
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y 셋팅
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로 세로 크기
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//맥스 프레임 x,y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }
};

