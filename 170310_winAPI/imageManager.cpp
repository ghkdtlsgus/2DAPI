#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}

//이미지 매니져 초기화
HRESULT imageManager::init()
{
	return S_OK;
}
//이미지 매니져 해제
void imageManager::release()
{
	deleteAll();
}

//키값으로 빈 비트맵 초기화
image* imageManager::addImage(string strKey, int width, int height)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다.
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
//키값으로 이미지 파일 초기화(주 사용)
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다.
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다.
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
//키값으로 프레임 이미지 파일로 초기화
image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다.
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다.
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//이미지 키값으로 찾기
image* imageManager::findImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL

	return NULL;
}
//이미지 키값으로 삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵에서 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}
//이미지 전체 삭제
BOOL imageManager::deleteAll()
{
	//맵 전체를 돌면서 지워서
	mapImageIter iter = _mImageList.begin();
	for (iter; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//맵 전체 삭제
	_mImageList.clear();

	return TRUE;

}

//==================================================================
//		## 일반렌더 ## 
//==================================================================
void imageManager::render(string strKey, HDC hdc)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//==================================================================
//		## 알파렌더 ## 
//==================================================================
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//==================================================================
//		## 프레임렌더 ## 
//==================================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
}

//==================================================================
//		## 루프렌더 ## 
//==================================================================
//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}
