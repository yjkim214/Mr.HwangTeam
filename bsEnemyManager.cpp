#include "stdafx.h"
#include "bsEnemyManager.h"
#include "bsEnemy.h"
#include "bsSlime.h"

#define ENEMY_PREVPOS_X		WINSIZEX * 0.1f
#define ENEMY_PREVPOS_Y1	WINSIZEY * 0.1f
#define ENEMY_PREVPOS_Y2	WINSIZEY * 0.4f
#define ENEMY_PREVPOS_Y3	WINSIZEY * 0.7f

HRESULT bsEnemyManager::init(void)
{
	addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
	addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
	addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);

	return S_OK;
}

void bsEnemyManager::release(void)
{
	for (int i = 0; i < _vEnemyList.size(); i++)
	{
		_vEnemyList[i]->release();
		SAFE_DELETE(_vEnemyList[i]);
	}

	_vEnemyList.clear();
}

void bsEnemyManager::update(void)
{
	for (int i = 0; i < _vEnemyList.size(); i++)
	{
		_vEnemyList[i]->update();
	}
}

void bsEnemyManager::render(void)
{
	for (int i = 0; i < _vEnemyList.size(); i++)
	{
		_vEnemyList[i]->render();
	}
}

void bsEnemyManager::addSlime(float prevX, float prevY)
{
	bsSlime* newSlime = new bsSlime;
	newSlime->init();
	newSlime->setPrevPos(prevX, prevY);
	_vEnemyList.push_back(newSlime);
}