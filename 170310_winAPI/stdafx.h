// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// gdi+ 
#include <ole2.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� �������
#include <iostream>
//���� ����ϴ� STL
#include <string>
#include <vector>
#include <list>
#include <map>

//=====================================
//	## ���� ���� ������� �̰��� �߰� ##
//=====================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "util.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "animationManager.h"
#include "Camera.h"
#include "gdipManager.h"
//=====================================
//	## �̱��� �߰� ##
//=====================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define ANIMATIONMANAGER animationManager::getSingleton()
#define CAMERA Camera::getSingleton()
#define GDIPMANAGER gdipManager::getSingleton()
//=====================================
//	## ���ӽ��佺 �߰� ##
//=====================================
using namespace MY_UTIL;
using namespace Gdiplus;
//=====================================
//	## �����ι� ## (������ �ʱ�ȭ ����)
//=====================================
#define WINNAME (LPTSTR)(TEXT("�˰� ����"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX 800 + 20 + 640	//����ȭ�� + ����� + ������ Ÿ���̹���
#define WINSIZEY 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU


//===================================================
//	## ��ũ�� �Լ� ## (���ΰ����� ������ �κп��� ���)
//===================================================
#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;} }
#define SAFE_RELEASE(p)		{if(p) {((p)->release(); (p) = NULL;}}


//===================================================
//	## �������� ## (�ν��Ͻ�, �������ڵ�, ���콺��ǥ)
//===================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
