#pragma once
#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase <keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//Ű�� �ѹ��� ������?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ������ �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��� �����ֳ�?
	bool isStayKeyDown(int key);
	//���Ű��?(ĸ����,�ѹ���)
	bool isToggleKey(int key);
	//���� ���ư����� ?
	bool isMouseWheel();


};

