#include "stdafx.h"
#include "mainMenuScene.h"

HRESULT mainMenuScene::init(void)
{
	rc[0] = RectMakeCenter(400, 340, 220, 50);
	rc[1] = RectMakeCenter(405, 430, 110, 50);
	rc[2] = RectMakeCenter(405, 515, 90, 50);

	isNewGame = false;
	isLoad = false;
	isExit = false;
	return S_OK;
}

void mainMenuScene::release(void)
{
}

void mainMenuScene::update(void)
{
	if (PtInRect(&rc[0], _ptMouse))
	{
		isNewGame = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("¸¶À»");
		}
	}
	else
	{
		isNewGame = false;
	}

	if (PtInRect(&rc[1], _ptMouse))
	{
		isLoad = true;
	}
	else
	{
		isLoad = false;
	}

	if (PtInRect(&rc[2], _ptMouse))
	{
		isExit = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}
	else
	{
		isExit = false;
	}
}

void mainMenuScene::render(void)
{
	IMAGEMANAGER->render("mainMenu", getMemDC());
	if (isNewGame == true)
	{
		IMAGEMANAGER->render("newGameSelect", getMemDC());
	}

	if (isLoad == true)
	{
		IMAGEMANAGER->render("loadSelect", getMemDC());
	}

	if (isExit == true)
	{
		IMAGEMANAGER->render("exitSelect", getMemDC());
	}
}
