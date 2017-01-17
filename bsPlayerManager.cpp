#include "stdafx.h"
#include "bsPlayerManager.h"
#include "bsPlayer.h"
#include "AlexNoah.h"
#include "Lunar.h"
#include "Tempest.h"

#define PLAYER_PREVPOS_X	WINSIZEX * 0.7f
#define PLAYER_PREVPOS_Y1	WINSIZEY * 0.1f
#define PLAYER_PREVPOS_Y2	WINSIZEY * 0.4f
#define PLAYER_PREVPOS_Y3	WINSIZEY * 0.7f

HRESULT bsPlayerManager::init(void)
{
	addAlexNoah(PLAYER_PREVPOS_X, PLAYER_PREVPOS_Y1);
	addLunar(PLAYER_PREVPOS_X, PLAYER_PREVPOS_Y2);
	addTempest(PLAYER_PREVPOS_X, PLAYER_PREVPOS_Y3);

	return S_OK;
}

void bsPlayerManager::release(void)
{
	for (int i = 0; i < _vPlayerList.size(); i++)
	{
		_vPlayerList[i]->release();
		SAFE_DELETE(_vPlayerList[i]);
	}

	_vPlayerList.clear();
}

void bsPlayerManager::update(void)
{
	for (int i = 0; i < _vPlayerList.size(); i++)
	{
		_vPlayerList[i]->update();
	}
}

void bsPlayerManager::render(void)
{
	for (int i = 0; i < _vPlayerList.size(); i++)
	{
		_vPlayerList[i]->render();
	}
}

void bsPlayerManager::addAlexNoah(float prevX, float prevY)
{
	AlexNoah* newAlexNoah = new AlexNoah;
	newAlexNoah->init();
	newAlexNoah->setPrevPos(prevX, prevY);
	_vPlayerList.push_back(newAlexNoah);
}

void bsPlayerManager::addLunar(float prevX, float prevY)
{
	Lunar* newLunar = new Lunar;
	newLunar->init();
	newLunar->setPrevPos(prevX, prevY);
	_vPlayerList.push_back(newLunar);
}

void bsPlayerManager::addTempest(float prevX, float prevY)
{
	Tempest* newTempest = new Tempest;
	newTempest->init();
	newTempest->setPrevPos(prevX, prevY);
	_vPlayerList.push_back(newTempest);
}