//=================================
//		## ��� ���� ##
//=================================
#include "stdafx.h"
#include "mainGame.h"

//=================================
//		## ���� ���� ##
//=================================
//�ν��Ͻ�(�޸𸮻� �Ҵ�Ǿ� �������� ���α׷�-> OS Ȯ���ϱ� ���� ��)
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };

//���ΰ��� Ŭ���� ����
mainGame* _mg;

//=================================
//		## �Լ� ������ Ÿ�� (�Լ� ����) ##
//=================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//������ �����Լ�
//hInstance : �ν��Ͻ� �ڵ�
//hPrevInstance : ������ ����� �ν��Ͻ� �ڵ�(������ ��� ����)
//lpszCmdParam : ��������� �Էµ� ���α׷� �μ�
//nCmdShow : ���α׷��� ���۵� ����(�ּ�ȭ, ����ũ�� ���)
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	//���ΰ��� Ŭ���� �����Ҵ�
	_mg = new mainGame;

	//�ν��Ͻ��� ���������� ��Ƶд�.
	//�ڵ� �ν��Ͻ�, ���α׷��� �ν��Ͻ� �ĺ���, 
	//���� ���� ���α׷� ��ü�� ��üȭ�� �ּ�, ���α׷� ��ü�� �ڵ�
	//�ڵ��̶�? �ü���� ���𰡸� �ĺ��ϱ� ���� Ű��
	_hInstance = hInstance;

	//�������� ����
	//1. ������ â ���� �� ȭ�鿡 ����
	//2. �޼��� ����

	//WNDCLASS : ������ â�� ������ �����ϱ� ���� ����ü
	//������â ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//������ Ŭ�������� ����ϰ��� �ϴ� ������ �޸𸮾��� ����Ʈ ������ ����
	wndClass.cbWndExtra = 0;	//cbClsExtra �����ϵ� ���� �����쿡�� ����ϰ��� �ϴ� ������ �޸𸮾��� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�������� �۾������� ĥ�� ��� �귯�ø� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŭ���� Ŀ���� ����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//Ÿ��Ʋ���� �»�ܿ� ������ �����ܰ� �����찡 �ּ�ȭ �Ǿ����� ������ �������� ����
	wndClass.hInstance = hInstance;	//������ Ŭ������ ����� �������α׷��� �ν��Ͻ� �ڵ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//�޼����� ó���Ѵ� �Լ��� ����(������ ���ν���)
	wndClass.lpszClassName = WINNAME;	//����ϰ��� �ϴ� ������ Ŭ�����̸�
	wndClass.lpszMenuName = NULL;	//Ŭ�����κ��� ������� �����찡 ����� �޴��� ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//������ Ŭ������ ��Ÿ���� ����

												//������ Ŭ���� ���
	RegisterClass(&wndClass);	//����� ������ Ŭ������ Ư���� �����ϴ� WNDCLASS ����ü�� ������ ����

								//������ â ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		WINSTARTX,				//������ ȭ�� X ��ǥ
		WINSTARTY,				//������ ȭ�� Y ��ǥ
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL);			//�������ְ� �׷��� ������ NULL(�츮�� ��� ���ϴϱ� NULL ����)

						//ȭ�� �۾� ������ �������
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);


	//ȭ�鿡 ������ �����ֱ�
	ShowWindow(_hWnd, nCmdShow);
	
	//���ΰ��� Ŭ���� �ʱ�ȭ�� �����ߴٸ� �ٷ� ������Ѷ�
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	//MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;


	
	//���ӿ� ����
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
	//		//�ʴ� 60���������� ������Ʈ ���Ѷ�
	//		TIMEMANAGER->update(60.0f);
	//		_mg->update();
	//		_mg->render();
	//	}
	//}
	


	//TranslateMessage : Ű���� �Է¸޽��� ó�� ���
	//�Էµ� Ű�� �������� Ȯ�� �� �빮��,�ҹ���,�ѱ�,������� 
	//WM_CHAR�޼����� �߻� ��Ų��.

	//DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �������ش�.

	//�޼��� ����
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//���ΰ��� Ŭ���� ����
	_mg->release();
	//������ Ŭ���� �������
	UnregisterClass(WINNAME, hInstance);
	return message.wParam;
}

//������ ���ν���: �޼����� �ü���� ���� ������ �ü���� ȣ�����ش�.
//hWnd : ��� �����쿡�� �߻��� �޼������� ����
//iMessage : �޼��� ���й�ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� �����Ѵ�.
//lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����
//CALLBACK �Լ��� � �̺�Ʈ�� �߻� ���� �� ������ �ȷ��޶�� �ϴ� ��! �� ȣ�� �Ǵ� ���̶�� ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//���ΰ��� Ŭ������ �������ν����� ���� ��Ų��.
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//===================================================================
//		## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//===================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� RECT ������ ������ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
