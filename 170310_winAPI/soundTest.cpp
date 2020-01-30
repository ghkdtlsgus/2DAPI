#include "stdafx.h"
#include "soundTest.h"

soundTest::soundTest()
{
}

soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{
	SOUNDMANAGER->addSound("����3", "sound/����3.wav", true, true);
	SOUNDMANAGER->play("����3");
	return S_OK;
}

void soundTest::release()
{
}

void soundTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->pause("����3");
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		SOUNDMANAGER->resume("����3");
	}
}

void soundTest::render()
{
}
