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

	//키가 한번만 눌럿냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려있냐?
	bool isStayKeyDown(int key);
	//토글키냐?(캡스락,넘버락)
	bool isToggleKey(int key);
	//휠이 돌아갔느냐 ?
	bool isMouseWheel();


};

