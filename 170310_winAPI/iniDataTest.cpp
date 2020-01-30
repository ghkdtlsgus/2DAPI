#include "stdafx.h"
#include "iniDataTest.h"


iniDataTest::iniDataTest()
{
}


iniDataTest::~iniDataTest()
{
}

HRESULT iniDataTest::init()
{
	return S_OK;
}

void iniDataTest::release()
{
}

void iniDataTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		INIDATA->addData("정흠", "지각", "1000");
		INIDATA->addData("정훈", "성실함", "100");
		INIDATA->addData("기봉", "출석률", "0");

		INIDATA->iniSave("8CLASS");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int test = INIDATA->loadDataIntger("8CLASS", "정흠", "지각");
		cout << test << endl;
	}
}

void iniDataTest::render()
{
}
