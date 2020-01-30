// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// gdi+ 
#include <ole2.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더파일
#include <iostream>
//자주 사용하는 STL
#include <string>
#include <vector>
#include <list>
#include <map>

//=====================================
//	## 내가 만든 헤더파일 이곳에 추가 ##
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
//	## 싱글톤 추가 ##
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
//	## 네임스페스 추가 ##
//=====================================
using namespace MY_UTIL;
using namespace Gdiplus;
//=====================================
//	## 디파인문 ## (윈도우 초기화 셋팅)
//=====================================
#define WINNAME (LPTSTR)(TEXT("검과 마법"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX 800 + 20 + 640	//왼쪽화면 + 빈공간 + 오른쪽 타일이미지
#define WINSIZEY 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU


//===================================================
//	## 매크로 함수 ## (메인게임의 릴리즈 부분에서 사용)
//===================================================
#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;} }
#define SAFE_RELEASE(p)		{if(p) {((p)->release(); (p) = NULL;}}


//===================================================
//	## 전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//===================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
