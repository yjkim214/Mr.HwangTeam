#include "stdafx.h"
#include "battleScene.h"
#include "bsPlayerManager.h"
#include "bsPlayer.h"
#include "bsEnemyManager.h"
#include "bsEnemy.h"

HRESULT battleScene::init(void)
{
	_pm = new bsPlayerManager;
	_pm->init();

	_em = new bsEnemyManager;
	_em->init();

	_currentPlayerIndex = 0;
	_currentEnemyIndex = 0;

	//먼저 에너미 턴부터
	_bsState = ENEMYTURN;

	return S_OK;
}

void battleScene::release(void)
{
	_em->release();
	SAFE_DELETE(_em);

	_pm->release();
	SAFE_DELETE(_pm);
}

void battleScene::update(void)
{
	//플레이어가 이겼을시
	if (_em->getVEnemyList()[0]->getIsDead() && _em->getVEnemyList()[1]->getIsDead() && _em->getVEnemyList()[2]->getIsDead())
	{

	}

	if (_pm->getVPlayerList()[0]->getIsDead() && _pm->getVPlayerList()[1]->getIsDead() && _pm->getVPlayerList()[2]->getIsDead())
	{

	}

	else
	{
		if (_bsState == PLAYERTURN)
		{

		}

		else if (_bsState == ENEMYTURN)
		{
			while (true)
			{
				if (_em->getVEnemyList()[_currentEnemyIndex]->getIsDead())
				{
					_currentEnemyIndex++;
				}

				else
				{
					break;
				}
			}

			if (_em->getVEnemyList()[_currentEnemyIndex]->getTurnState() == NOTMYTURN)
			{
				int rand = 0;

				while (true)
				{
					rand = RND->getInt(_pm->getVPlayerList().size());

					if (!_pm->getVPlayerList()[rand]->getIsDead())
					{
						break;
					}
				}

				_em->getVEnemyList()[_currentEnemyIndex]->myTurn();
				_em->getVEnemyList()[_currentEnemyIndex]->setDestPos(_pm->getVPlayerList()[rand]->getPrevPos().x - 100, _pm->getVPlayerList()[rand]->getPrevPos().y);
			}

			else if (_em->getVEnemyList()[_currentEnemyIndex]->getTurnState() == TURNEND)
			{
				if (_currentEnemyIndex + 1 < _em->getVEnemyList().size())
				{
					_currentEnemyIndex++;
				}

				else
				{
					_currentEnemyIndex = 0;
					_bsState = PLAYERTURN;
				}
			}
		}
	}

	_pm->update();
	_em->update();
}

void battleScene::render(void)
{
	_pm->render();
	_em->render();
}