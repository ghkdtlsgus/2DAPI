#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib")	//알파블랜드를 사용하기 위한 라이브러리 추가
//맴버 이니셜라이즈로 이미지 클래스 맴버변수 값을 바로 초기화 한다
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

//빈 비트맵 초기화
HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;


}
//이미지 리소스 초기화(사용안함)
HRESULT image::init(const DWORD resId, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resId;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//이미지 파일로 불러오는게 중요함
//이미지 파일 초기화
HRESULT image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
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

	//파일 이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
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

	//파일 이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 들어 잇다면 릴리즈 먼저 해줄 것!!
	if (_imageInfo != NULL) release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해주는 함수

	//이미지 정보 생성하기
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

	//파일 이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인 경우 AC_SRC_ALPHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌드 함수 사용 실패)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자

										//이미지 정보 생성하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

//투명키 셋팅
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//릴리즈
void image::release()
{
	//이미지 정보가 남아 있다면 릴리즈(해제) 해줄것
	if (_imageInfo)
	{
		//이미지삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hOBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//투명컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//랜더(내가 지정한 위치에 이미지를 출력한다)
void image::render(HDC hdc)
{
	if (_isTrans) //배경색 없앨거냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			0,						//복사될 좌표 시작점 x
			0,						//복사될 좌표 시작점 y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점 xy
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로키기
			_transColor);			//복사할때 제외할 색상(마젠타색상 지우기)
	}

	else//원본이미지 그대로 출력 할거냐?
	{
		//DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨거냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,						//복사될 좌표 시작점 x
			destY,						//복사될 좌표 시작점 y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점 xy
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로키기
			_transColor);			//복사할때 제외할 색상(마젠타색상 지우기)
	}
	else//원본이미지 그대로 출력 할거냐?
	{
		//DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //배경색 없앨거냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,				//복사될 장소의 DC
			destX,				//복사될 좌표 시작점 x
			destY,				//복사될 좌표 시작점 y
			sourWidth,			//복사될 이미지 가로크기
			sourHeight,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,	//복사될 대상 DC
			sourX, sourY,		//복사 시작지점 xy
			sourWidth,			//복사 영역 가로크기
			sourHeight,			//복사 영역 세로키기
			_transColor);		//복사할때 제외할 색상(마젠타색상 지우기)
	}
	else//원본이미지 그대로 출력 할거냐?
	{
		//DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드 사용할 수 있도록 초기화
	if (!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	//배경색(마젠타) 없앤 후 알파블렌딩 할거냐?
	if (_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그려준다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc,
			destX, destY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타값 없애줌)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다.
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//알파블렌드 사용할 수 있도록 초기화
	if (!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	//배경색(마젠타) 없앤 후 알파블렌딩 할거냐?
	if (_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그려준다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc,
			destX, destY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타값 없애줌)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨거냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			_imageInfo->frameWidth,	//복사될 이미지 가로크기
			_imageInfo->frameHeight,//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, //복사 시작지점 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작지점 y
			_imageInfo->frameWidth,			//복사 영역 가로크기
			_imageInfo->frameHeight,		//복사 영역 세로키기
			_transColor);			//복사할때 제외할 색상(마젠타색상 지우기)
	}
	else//원본이미지 그대로 출력 할거냐?
	{
		//DC간의 영역끼리 서로 고속복사를 해주는 함수
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

	if (_isTrans) //배경색 없앨거냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			_imageInfo->frameWidth,	//복사될 이미지 가로크기
			_imageInfo->frameHeight,//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, //복사 시작지점 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작지점 y
			_imageInfo->frameWidth,			//복사 영역 가로크기
			_imageInfo->frameHeight,		//복사 영역 세로키기
			_transColor);			//복사할때 제외할 색상(마젠타색상 지우기)
	}
	else//원본이미지 그대로 출력 할거냐?
	{
		//DC간의 영역끼리 서로 고속복사를 해주는 함수
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
	//offset값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 소스의 영역(이미지)를 셋팅할 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어 갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그름의 값만큼 바텀 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 로프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양 만큼 라이트 값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그리자
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}

}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 소스의 영역(이미지)를 셋팅할 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어 갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그름의 값만큼 바텀 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 로프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양 만큼 라이트 값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그리자
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}

}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
