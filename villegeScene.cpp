#include "stdafx.h"
#include "villegeScene.h"

HRESULT villegeScene::init(void)
{
	return S_OK;
}

void villegeScene::release(void)
{
}

void villegeScene::update(void)
{
}

void villegeScene::render(void)
{
	IMAGEMANAGER->render("village", getMemDC());
}
