#include "stdafx.h"
#include "bsEnemyManager.h"
#include "bsEnemy.h"
#include "bsSlime.h"
#include "bsFluffyBug.h"
#include "bsFlytrapper.h"
#include "bsBarbarian.h"
#include "bsDevilBomber.h"

#define ENEMY_PREVPOS_X		WINSIZEX * 0.1f
#define ENEMY_PREVPOS_Y1	WINSIZEY * 0.3f
#define ENEMY_PREVPOS_Y2	WINSIZEY * 0.5f
#define ENEMY_PREVPOS_Y3	WINSIZEY * 0.7f

HRESULT bsEnemyManager::init(void)
{
	if(PLAYERDATA->getMonsterNumber() == 1)
	{
		addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
		addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
		addSlime(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);
	}

	if(PLAYERDATA->getMonsterNumber() == 2)
	{
		addFluffyBug(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
		addFluffyBug(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
		addFluffyBug(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);
	}

	if(PLAYERDATA->getMonsterNumber() == 3)
	{
		addFlytrapper(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
		addFlytrapper(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
		addFlytrapper(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);
	}

	if(PLAYERDATA->getMonsterNumber() == 4)
	{
		addBarbarian(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
		addBarbarian(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
		addBarbarian(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);
	}

	if(PLAYERDATA->getMonsterNumber() == 5)
	{
		addDevilBomber(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y1);
		addDevilBomber(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y2);
		addDevilBomber(ENEMY_PREVPOS_X, ENEMY_PREVPOS_Y3);
	}

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

void bsEnemyManager::addFluffyBug(float prevX, float prevY)
{
	bsFluffyBug* newFluffyBug = new bsFluffyBug;
	newFluffyBug->init();
	newFluffyBug->setPrevPos(prevX, prevY);
	_vEnemyList.push_back(newFluffyBug);
}

void bsEnemyManager::addFlytrapper(float prevX, float prevY)
{
	bsFlytrapper* newFlytrapper = new bsFlytrapper;
	newFlytrapper->init();
	newFlytrapper->setPrevPos(prevX, prevY);
	_vEnemyList.push_back(newFlytrapper);
}

void bsEnemyManager::addBarbarian(float prevX, float prevY)
{
	bsBarbarian* newBarbarian = new bsBarbarian;
	newBarbarian->init();
	newBarbarian->setPrevPos(prevX, prevY);
	_vEnemyList.push_back(newBarbarian);
}

void bsEnemyManager::addDevilBomber(float prevX, float prevY)
{
	bsDevilBomber* newDevilBomber = new bsDevilBomber;
	newDevilBomber->init();
	newDevilBomber->setPrevPos(prevX, prevY);
	_vEnemyList.push_back(newDevilBomber);
}

void bsEnemyManager::selectedEnemy(int select)
{
	for (int i = 0; i < _vEnemyList.size(); i++)
	{
		if (i == select)
		{
			_vEnemyList[i]->setIsSelected(true);
		}

		else
		{
			_vEnemyList[i]->setIsSelected(false);
		}
	}
}

void bsEnemyManager::endSelect()
{
	//모두 트루로
	for (int i = 0; i < _vEnemyList.size(); i++)
	{
		if (!_vEnemyList[i]->getIsDead())
		{
			_vEnemyList[i]->setIsSelected(true);
		}
	}
}