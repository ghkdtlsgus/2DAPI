#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	


	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{

	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		GDIPMANAGER->init();
	}

	return S_OK;
}

void gameNode::release()
{

	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니져 싱글톤 해제
		KEYMANAGER->releaseSingleton();
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		GDIPMANAGER->release();
		GDIPMANAGER->releaseSingleton();
	}
	
	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	//나중에 고성능 타이머를 만든 후에는 사용하지 않는다.
	//더블버퍼링 이후 사용하지 않는다 (true->false)
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render()
{
}




LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (iMessage)
	{

	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		//마우스 좌표값 셋팅
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_COMMAND:
		//프로그램 실행중 사용자가 메뉴 항목을 선택하면 발생하는 메세지
		switch (LOWORD(wParam))
		{
		case CTRL_H_edit:
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
