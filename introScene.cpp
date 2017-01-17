#include "stdafx.h"
#include "introScene.h"

HRESULT introScene::init(void)
{
	_startImage = IMAGEMANAGER->addFrameImage("intro", "intro.bmp", 1599, WINSIZEY, 2, 1, false);
	SOUNDMANAGER->addSound("introMusic", "introMusic.MID", true, true);
	SOUNDMANAGER->play("introMusic");
	frameX = 0;
	time = 0;
	return S_OK;
}

void introScene::release(void)
{
}

void introScene::update(void)
{
	time++;
	if (time % 10 == 0)
	{
		frameX++;
		if (frameX > 2)
		{
			frameX = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("로딩화면");
		if (SOUNDMANAGER->isPlaySound("introMusic"))
		{
			SOUNDMANAGER->stop("introMusic");
		}
	}
}

void introScene::render(void)
{
	_startImage->frameRender(getMemDC(), 0, 0, frameX, 0);
}
