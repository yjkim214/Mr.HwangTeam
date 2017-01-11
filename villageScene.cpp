#include "stdafx.h"
#include "villageScene.h"

HRESULT villageScene::init(void)
{
	_villageMap = new villageMap;
	_villageMap->init();
	return S_OK;
}

void villageScene::release(void)
{
	_villageMap->release();
	SAFE_DELETE(_villageMap);
}

void villageScene::update(void)
{
	_villageMap->update();
}

void villageScene::render(void)
{
	_villageMap->render();
}
