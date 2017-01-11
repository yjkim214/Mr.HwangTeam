#include "stdafx.h"
#include "villageMap.h"


HRESULT villageMap::init(void)
{
	_bgX = 0;
	_bgY = 0;
	return S_OK;
}

void villageMap::release(void)
{
}

void villageMap::update(void)
{
}

void villageMap::render(void)
{
	IMAGEMANAGER->render("village", getMemDC(), _bgX, _bgY);
}
