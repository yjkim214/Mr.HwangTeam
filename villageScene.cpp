#include "stdafx.h"
#include "villageScene.h"

HRESULT villageScene::init(void)
{
	_villageMap = new villageMap;
	_villageMap->init();

	_Owplayer = new Owplayer;
	_Owplayer->init();

	_villageMap->setOWPlayer(_Owplayer);
	_Owplayer->setScene(_villageMap);
	return S_OK;
}

void villageScene::release(void)
{
	_villageMap->release();
	SAFE_DELETE(_villageMap);

	_Owplayer->release();
	SAFE_DELETE(_Owplayer);
}

void villageScene::update(void)
{
	_villageMap->update();
	_Owplayer->update();
}

void villageScene::render(void)
{
	_villageMap->render();
	_Owplayer->render();
}
