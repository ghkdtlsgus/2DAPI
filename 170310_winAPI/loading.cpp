#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	m_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü
	memset(&m_imageResource, 0, sizeof(tagImageResource));

	m_imageResource.keyName = keyName;
	m_imageResource.width = width;
	m_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	m_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü
	memset(&m_imageResource, 0, sizeof(tagImageResource));

	m_imageResource.keyName = keyName;
	m_imageResource.fileName = fileName;
	m_imageResource.width = width;
	m_imageResource.height = height;
	m_imageResource.trans = isTrans;
	m_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	m_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü
	memset(&m_imageResource, 0, sizeof(tagImageResource));

	m_imageResource.keyName = keyName;
	m_imageResource.fileName = fileName;
	m_imageResource.x = x;
	m_imageResource.y = y;
	m_imageResource.width = width;
	m_imageResource.height = height;
	m_imageResource.trans = isTrans;
	m_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	m_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü
	memset(&m_imageResource, 0, sizeof(tagImageResource));

	m_imageResource.keyName = keyName;
	m_imageResource.fileName = fileName;
	m_imageResource.width = width;
	m_imageResource.height = height;
	m_imageResource.frameX = frameX;
	m_imageResource.frameY = frameY;
	m_imageResource.trans = isTrans;
	m_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	m_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü
	memset(&m_imageResource, 0, sizeof(tagImageResource));

	m_imageResource.keyName = keyName;
	m_imageResource.fileName = fileName;
	m_imageResource.x = x;
	m_imageResource.y = y;
	m_imageResource.width = width;
	m_imageResource.height = height;
	m_imageResource.frameX = frameX;
	m_imageResource.frameY = frameY;
	m_imageResource.trans = isTrans;
	m_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �ʱ�ȭ
	m_backGround = IMAGEMANAGER->addImage("���", "images/���.bmp", WINSIZEX, WINSIZEY);

	//�ε��� �ʱ�ȭ
	m_loadingBar = new progressBar;
	m_loadingBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 100, 500, 600, 20);
	m_loadingBar->setGauge(0, 0);
	
	//�ε��� ������ �ʱ�ȭ
	m_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	//�ε��� ����
	SAFE_DELETE(m_loadingBar);
}

void loading::update()
{
	m_loadingBar->update();
}

void loading::render()
{
	//��׶��� ����
	m_backGround->render(getMemDC());
	m_loadingBar->render();
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	m_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height,frameX, frameY, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	if (m_currentGauge >= m_vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = m_vLoadItem[m_currentGauge];

	tagImageResource img = item->getImageResource();

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		break;	

	case LOAD_KIND_IMAGE_1:
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		break;

	case LOAD_KIND_IMAGE_2:
		IMAGEMANAGER->addImage(img.keyName, img.fileName,img.x,img.y, img.width, img.height, img.trans, img.transColor);
		break;

	case LOAD_KIND_FRAMEIMAGE_0:
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height,img.frameX, img.frameY, img.trans, img.transColor);
		break;

	case LOAD_KIND_FRAMEIMAGE_1:
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName,img.x,img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
		
		//���ε��� ä�� ������
	case LOAD_KIND_SOUND:
		break;
	}

	//�ε��� �̹��� ����
	m_loadingBar->setGauge(m_currentGauge, m_vLoadItem.size());
	
	//ī��Ʈ
	m_currentGauge++;

	return FALSE;
}
