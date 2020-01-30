//=================================
//		## 헤더 파일 ##
//=================================
#include "stdafx.h"
#include "mainGame.h"

//=================================
//		## 전역 변수 ##
//=================================
//인스턴스(메모리상에 할당되어 실행중인 프로그램-> OS 확인하기 위한 값)
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };

//메인게임 클래스 선언
mainGame* _mg;

//=================================
//		## 함수 프로토 타입 (함수 원형) ##
//=================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//윈도우 메인함수
//hInstance : 인스턴스 핸들
//hPrevInstance : 이전에 실행된 인스턴스 핸들(지금은 사용 안함)
//lpszCmdParam : 명령행으로 입력된 프로그램 인수
//nCmdShow : 프로그램이 시작될 형태(최소화, 보통크기 등등)
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	//메인게임 클래스 동적할당
	_mg = new mainGame;

	//인스턴스를 전역변수에 담아둔다.
	//핸들 인스턴스, 프로그램의 인스턴스 식별자, 
	//쉽게 보면 프로그램 자체의 실체화된 주소, 프로그램 자체의 핸들
	//핸들이란? 운영체제가 무언가를 식별하기 위한 키값
	_hInstance = hInstance;

	//윈메인의 역할
	//1. 윈도우 창 세팅 후 화면에 띄우기
	//2. 메세지 루프

	//WNDCLASS : 윈도우 창의 정보를 저장하기 위한 구조체
	//윈도우창 구조체 선언 후 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//윈도우 클래스에서 사용하고자 하는 여분의 메모리양을 바이트 단위로 지정
	wndClass.cbWndExtra = 0;	//cbClsExtra 유사하되 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우의 작업영역에 칠할 배경 브러시를 지정
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//클래스 커서를 지정
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//타이틀바의 좌상단에 보여줄 아이콘과 윈도우가 최소화 되었을때 보여줄 아이콘을 지정
	wndClass.hInstance = hInstance;	//윈도우 클래스를 등록한 응용프로그램의 인스턴스 핸들
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//메세지를 처리한는 함수를 지정(윈도우 프로시져)
	wndClass.lpszClassName = WINNAME;	//등록하고자 하는 윈도우 클래스이름
	wndClass.lpszMenuName = NULL;	//클래스로부터 만들어진 윈도우가 사용할 메뉴를 지정
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//윈도우 클래스의 스타일을 지정

												//윈도우 클래스 등록
	RegisterClass(&wndClass);	//등록할 윈도우 클래스의 특성을 지정하는 WNDCLASS 구조체의 번지를 전달

								//윈도우 창 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 화면 X 좌표
		WINSTARTY,				//윈도우 화면 Y 좌표
		WINSIZEX,				//윈도우 화면 가로크기
		WINSIZEY,				//윈도우 화면 세로크기
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL);			//지정해주고 그렇지 않으면 NULL(우리는 사용 안하니까 NULL 고정)

						//화면 작업 사이즈 영역계산
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);


	//화면에 윈도우 보여주기
	ShowWindow(_hWnd, nCmdShow);
	
	//메인게임 클래스 초기화를 실패했다면 바로 종료시켜라
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	//MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;


	
	//게임용 루프
	//while(true)
	//{
	//	if(PeekMessage(&message, NULL,0,0,PM_REMOVE))
	//	{
	//		if(message.message == WM_QUIT) break;
	//		TranslateMessage(&message);
	//		DispatchMessage(&message);
	//	}
	//	else
	//	{
	//		//초당 60프레임으로 업데이트 시켜라
	//		TIMEMANAGER->update(60.0f);
	//		_mg->update();
	//		_mg->render();
	//	}
	//}
	


	//TranslateMessage : 키보드 입력메시지 처리 담당
	//입력된 키가 문자인지 확인 후 대문자,소문자,한글,영문등등 
	//WM_CHAR메세지를 발생 시킨다.

	//DispatchMessage : 윈도우 프로시져에서 전달된 메세지를 실제 윈도우로 전달해준다.

	//메세지 루프
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//메인게임 클래스 해제
	_mg->release();
	//윈도우 클래스 등록해제
	UnregisterClass(WINNAME, hInstance);
	return message.wParam;
}

//윈도우 프로시져: 메세지를 운영체제에 전달 강제로 운영체제가 호출해준다.
//hWnd : 어느 윈도우에서 발생한 메세지인지 구분
//iMessage : 메세지 구분번호
//wParam : unsigned int 마우스 버튼의 상태, 키보드 조합키의 상태를 전달한다.
//lParam : unsigned long 마우스 클릭 좌표를 전달
//CALLBACK 함수는 어떤 이벤트가 발생 했을 때 나에게 안려달라고 하는 것! 즉 호출 되는 것이라고 봐야함
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//메인게임 클래스의 메인프로시져를 실행 시킨다.
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//===================================================================
//		## 윈도우 크기 조정 ## (클라이언트 영역의 사이즈를 정확히 잡아준다)
//===================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
