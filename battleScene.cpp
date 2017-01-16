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
	_bsState = PLAYERTURN;
	_userSelect = INIT;

	_actionSelected = 4;
	_enemySelected = 0;

	_uiAttack = IMAGEMANAGER->findImage("bsUi_Attack");
	_uiSkill = IMAGEMANAGER->findImage("bsUi_Skill");
	_uiDefense = IMAGEMANAGER->findImage("bsUi_Defense");
	_uiGetaway = IMAGEMANAGER->findImage("bsUi_Getaway");

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
			setPlayerIndex();

			if (_userSelect == INIT)
			{
				if (_actionSelected != 0)
				{
					_actionSelected = 0;
				}

				_userSelect = SELECTED;
			}

			selectAction();

			if (_userSelect == ATTACK)
			{
				if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == NOTMYTURN)
				{
					selectEnemy();

					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
					{
						_pm->getVPlayerList()[_currentPlayerIndex]->myTurnAttack(_enemySelected);
						_em->endSelect();
					}
				}

				else if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == MYTURN)
				{
					if (_pm->getVPlayerList()[_currentPlayerIndex]->getIsAttack())
					{
						_em->getVEnemyList()[_enemySelected]->getDmg(_pm->getVPlayerList()[_currentPlayerIndex]->getAtt());
						_pm->getVPlayerList()[_currentPlayerIndex]->setIsAttack(false);
					}
				}

				else if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == TURNEND)
				{
					if (_currentPlayerIndex + 1 < _pm->getVPlayerList().size())
					{
						_currentPlayerIndex++;
					}

					else
					{
						_currentPlayerIndex = 0;
						_bsState = ENEMYTURN;
					}

					_userSelect = INIT;
				}
			}

			if (_userSelect == SKILL)
			{
				if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == NOTMYTURN)
				{
					selectEnemy();

					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
					{
						_pm->getVPlayerList()[_currentPlayerIndex]->myTurnSkill(_enemySelected);
						_em->endSelect();
					}
				}

				else if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == MYTURN)
				{
					if (_pm->getVPlayerList()[_currentPlayerIndex]->getIsAttack())
					{
						_em->getVEnemyList()[_enemySelected]->getDmg(_pm->getVPlayerList()[_currentPlayerIndex]->getAtt());
						_pm->getVPlayerList()[_currentPlayerIndex]->setIsAttack(false);
					}
				}

				else if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == TURNEND)
				{
					if (_currentPlayerIndex + 1 < _pm->getVPlayerList().size())
					{
						_currentPlayerIndex++;
					}

					else
					{
						_currentPlayerIndex = 0;
						_bsState = ENEMYTURN;
					}

					_userSelect = INIT;
				}
			}

			if (_userSelect == DEFENSE)
			{
				_userSelect = INIT;
			}

			if (_userSelect == GETAWAY)
			{
				_userSelect = INIT;
			}
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

				_em->getVEnemyList()[_currentEnemyIndex]->myTurnAttack(rand);
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

	setUiImage();

	_pm->update();
	_em->update();
}

void battleScene::render(void)
{
	_pm->render();
	_em->render();

	_uiAttack->render(getMemDC());
	_uiSkill->render(getMemDC());
	_uiDefense->render(getMemDC());
	_uiGetaway->render(getMemDC());
}

void battleScene::setPlayerIndex()
{
	while (true)
	{
		if (_pm->getVPlayerList()[_currentPlayerIndex]->getIsDead())
		{
			_currentPlayerIndex++;
		}

		else
		{
			break;
		}
	}
}

void battleScene::selectAction()
{
	if (_userSelect == SELECTED)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_actionSelected++;

			if (_actionSelected > 3)
			{
				_actionSelected = 0;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_actionSelected--;

			if (_actionSelected < 0)
			{
				_actionSelected = 3;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_userSelect = static_cast<USER_SELECT>(_actionSelected);
		}
	}
}

void battleScene::selectEnemy()
{
	while (true)
	{
		if (_em->getVEnemyList()[_enemySelected]->getIsDead())
		{
			_enemySelected++;
		}

		else
		{
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_enemySelected > 0)
		{
			_enemySelected--;

			while (true)
			{
				if (_em->getVEnemyList()[_enemySelected]->getIsDead())
				{
					if (_enemySelected > 0)
					{
						_enemySelected--;
					}
				}

				else
				{
					break;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_enemySelected < _em->getVEnemyList().size() - 1)
		{
			_enemySelected++;

			while (true)
			{
				if (_em->getVEnemyList()[_enemySelected]->getIsDead())
				{
					if (_enemySelected > 0)
					{
						_enemySelected++;
					}
				}

				else
				{
					break;
				}
			}
		}
	}

	_em->selectedEnemy(_enemySelected);
}

void battleScene::setEnemyIndex()
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
}

void battleScene::setUiImage()
{
	if (_actionSelected == 0)
	{
		_uiAttack = IMAGEMANAGER->findImage("bsUi_Attack_Selected");
		_uiAttack->setCenter(570, 50);
	}

	else
	{
		_uiAttack = IMAGEMANAGER->findImage("bsUi_Attack");
		_uiAttack->setCenter(570, 50);
	}

	if (_actionSelected == 1)
	{
		_uiSkill = IMAGEMANAGER->findImage("bsUi_Skill_Selected");
		_uiSkill->setCenter(630, 50);
	}

	else
	{
		_uiSkill = IMAGEMANAGER->findImage("bsUi_Skill");
		_uiSkill->setCenter(630, 50);
	}

	if (_actionSelected == 2)
	{
		_uiDefense = IMAGEMANAGER->findImage("bsUi_Defense_Selected");
		_uiDefense->setCenter(690, 50);
	}

	else
	{
		_uiDefense = IMAGEMANAGER->findImage("bsUi_Defense");
		_uiDefense->setCenter(690, 50);
	}


	if (_actionSelected == 3)
	{

	}

	else
	{
		_uiGetaway = IMAGEMANAGER->findImage("bsUi_Getaway");
		_uiGetaway->setCenter(750, 50);
	}
}