#include "stdafx.h"
#include "gdipManager.h"


gdipManager::gdipManager()
{
}

gdipManager::~gdipManager()
{

}

HRESULT gdipManager::init()
{
	//gdi+ �ʱ�ȭ
	GdiplusStartupInput         m_GdiplusStartupInput;
	ULONG_PTR                   m_GdiplusToken;
	GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

	return S_OK;
}

void gdipManager::release()
{
	delAll();
}

void gdipManager::update()
{
}

void gdipManager::render()
{
	
}

bool gdipManager::IsValid(Gdiplus::Image * img) const
{
	//�̹��� ���� ���� Ȯ��
	return (NULL != img);
}

bool gdipManager::delAll()
{
	//�� ����������
	timgList iter = imgList.begin();
	for (iter; iter != imgList.end();) {
		if (iter->second != NULL) {
			SAFE_DELETE(iter->second);
			iter = imgList.erase(iter);
		}
		else 
			++iter;
	}
	imgList.clear();

	return TRUE;
}

gdipimage* gdipManager::findImg(string strKey)
{
	//�̹��� �Ŵ����� �����ϴ�
	timgList key = imgList.find(strKey);

	if (key != imgList.end())
	{
		return key->second;
	}
		

	return NULL;
}
gdipimage* gdipManager::addImg(string strKey, const char * path, int x, int y)
{
	// ASCII -> UNICODE �� ��ȯ
	wchar_t wPath[256];
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, path, -1, wPath, _countof(wPath));

	gdipimage *gdipimg;
	/*Run - Time Check Failure #3 - The variable 'gdipimg' is being used without being initialized.*/
	//�����ڴ� �ʼ�
	gdipimg = new gdipimage;

	//������ �ҷ����� ������Ҹ� �Ҵ��Ѵ�
	gdipimg->gimg = Image::FromFile(wPath);

	if (gdipimg->gimg) {
		gdipimg->gx = x;
		gdipimg->gy = y;

		gdipimg->gwidth = float(gdipimg->gimg->GetWidth()) / gdipimg->gx;
		gdipimg->gheight = float(gdipimg->gimg->GetHeight()) / gdipimg->gy;

		imgList.insert(make_pair(strKey, gdipimg));
		return gdipimg;
	}
	return NULL;
}

void gdipManager::render(HDC hdc, string strKey, int x, int y)
{
	//Ű�� ã��
	gdipimage *gdipimg = findImg(strKey);

	//�����ϰ� Ȯ�� �ѹ� �ϰ�
	//if (!IsValid(gdipimg->gimg))
	//	return;

	//�׸� ��ġ�� ����ش�
	RectF dst(float(x), float(y), gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst);
	G.ReleaseHDC(hdc);
}
void gdipManager::renderimgsize(HDC hdc, string strKey, int height, int width, int x, int y)
{
	//Ű�� ã��
	gdipimage *gdipimg = findImg(strKey);

	//�����ϰ� Ȯ�� �ѹ� �ϰ�
	//if (!IsValid(gdipimg->gimg))
	//	return;

	//�׸� ��ġ�� ����ش�
	RectF dst(float(x), float(y), width, height);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst);
	G.ReleaseHDC(hdc);
}
// float size  =  avreg 1.0;
void gdipManager::rendersize(HDC hdc, string strKey,float size, int x, int y)
{
	//Ű�� ã��
	gdipimage *gdipimg = findImg(strKey);

	//�����ϰ� Ȯ�� �ѹ� �ϰ�
	//if (!IsValid(gdipimg->gimg))
	//	return;

	// �̹��� �����ϸ�
	//�׸� ��ġ�� ����ش�
	RectF dst(float(x), float(y), gdipimg->gwidth * size, gdipimg->gheight * size);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderXFlip(HDC hdc, string strKey,float size ,int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);
	RectF dst(float(x), float(y), gdipimg->gwidth * size  , gdipimg->gheight * size );

	gdipimg->gimg->RotateFlip(Rotate180FlipX);
	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst); 
	gdipimg->gimg->RotateFlip(Rotate180FlipX);
	G.ReleaseHDC(hdc);

}

void gdipManager::renderF(HDC hdc, string strKey, int frameX, int frameY, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	RectF dst(float(x), float(y), gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst, frameX * gdipimg->gwidth, frameY * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFsize(HDC hdc, string strKey, float size, int frameX, int frameY, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	RectF dst(float(x), float(y), gdipimg->gwidth * size, gdipimg->gheight * size);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst, frameX * gdipimg->gwidth, frameY * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFXFlip(HDC hdc, string strKey, float size, int frameX, int frameY, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	RectF dst(float(x), float(y), gdipimg->gwidth * size, gdipimg->gheight * size);
	gdipimg->gimg->RotateFlip(Rotate180FlipX);
	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst, frameX * gdipimg->gwidth, frameY * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	gdipimg->gimg->RotateFlip(Rotate180FlipX);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFHorizontal(HDC hdc, string strKey, int frame, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	RectF dst(float(x), float(y), gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst, frame * gdipimg->gwidth, 0, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFVertical(HDC hdc, string strKey, int frame, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	RectF dst(float(x), float(y), gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);
	G.DrawImage(gdipimg->gimg, dst, 0, frame * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderR(HDC hdc, string strKey, float angle, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	PointF pf(x, y);
	PointF dst(pf.X - gdipimg->gwidth / 2, pf.Y - gdipimg->gheight / 2);

	Graphics G(hdc);

	G.TranslateTransform(pf.X, pf.Y);
	G.RotateTransform(angle);
	G.TranslateTransform(-pf.X, -pf.Y);
	G.DrawImage(gdipimg->gimg, dst);

	G.ReleaseHDC(hdc);
}

void gdipManager::renderFR(HDC hdc, string strKey, int frameX, int frameY, float angle, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	PointF pf(x, y);
	RectF dst(pf.X - gdipimg->gwidth / 2, pf.Y - gdipimg->gheight / 2, gdipimg->gwidth, gdipimg->gheight);
	
	Graphics G(hdc);

	G.TranslateTransform(pf.X, pf.Y);
	G.RotateTransform(angle);
	G.TranslateTransform(-pf.X, -pf.Y);
	G.DrawImage(gdipimg->gimg, dst, frameX * gdipimg->gwidth, frameY * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFRHorizontal(HDC hdc, string strKey, int frame, float angle, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	PointF pf(x, y);
	RectF dst(pf.X - gdipimg->gwidth / 2, pf.Y - gdipimg->gheight / 2, gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);

	G.TranslateTransform(pf.X, pf.Y);
	G.RotateTransform(angle);
	G.TranslateTransform(-pf.X, -pf.Y);
	G.DrawImage(gdipimg->gimg, dst, frame * gdipimg->gwidth, 0, gdipimg->gwidth, gdipimg->gheight, UnitPixel);
	G.ReleaseHDC(hdc);
}

void gdipManager::renderFRVertical(HDC hdc, string strKey, int frame, float angle, int x, int y)
{
	gdipimage *gdipimg = findImg(strKey);

	//if (!IsValid(gdipimg->gimg))
	//	return;

	PointF pf(x, y);
	RectF dst(pf.X - gdipimg->gwidth / 2, pf.Y - gdipimg->gheight / 2, gdipimg->gwidth, gdipimg->gheight);

	Graphics G(hdc);

	G.TranslateTransform(pf.X, pf.Y);
	G.RotateTransform(angle);
	G.TranslateTransform(-pf.X, -pf.Y);
	G.DrawImage(gdipimg->gimg, dst, 0, frame * gdipimg->gheight, gdipimg->gwidth, gdipimg->gheight, UnitPixel);

	G.ReleaseHDC(hdc);
}
