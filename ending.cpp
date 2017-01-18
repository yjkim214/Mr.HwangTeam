#include "stdafx.h"
#include "ending.h"

HRESULT ending::init(void)
{
	_ending = IMAGEMANAGER->findImage("ending");
	FrameX = 0;
	count = 0;
	return S_OK;
}

void ending::release(void)
{
}

void ending::update(void)
{
	count++;
	if (count % 100 == 0)
	{
		FrameX++;
	}
	if (FrameX >= 4 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("메인메뉴");
	}
}

void ending::render(void)
{
	_ending->frameRender(getMemDC(), 0, 0, FrameX, 0);
}
