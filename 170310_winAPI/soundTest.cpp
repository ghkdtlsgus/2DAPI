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
	SOUNDMANAGER->addSound("영전3", "sound/영전3.wav", true, true);
	SOUNDMANAGER->play("영전3");
	return S_OK;
}

void soundTest::release()
{
}

void soundTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->pause("영전3");
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		SOUNDMANAGER->resume("영전3");
	}
}

void soundTest::render()
{
}
