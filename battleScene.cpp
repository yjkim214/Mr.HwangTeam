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
	_enemyTurnState = ENEMYTURNSTATE::START;
	_playerTurnState = PLAYERTURNSTATE::START;

	_actionSelected = 4;
	_enemySelected = 0;
	_playerSelected = 0;

	_uiAttack = IMAGEMANAGER->findImage("bsUi_Attack");
	_uiSkill = IMAGEMANAGER->findImage("bsUi_Skill");
	_uiDefense = IMAGEMANAGER->findImage("bsUi_Defense");
	_uiGetaway = IMAGEMANAGER->findImage("bsUi_Getaway");

	int rand = RND->getInt(2);
	
	if (rand == 0)
	{
		_background = IMAGEMANAGER->findImage("bsBackground01");
	}

	else if (rand == 1)
	{
		_background = IMAGEMANAGER->findImage("bsBackground02");
	}

	SOUNDMANAGER->play("battleMusic");

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
		for (int i = 0; i < _pm->getVPlayerList().size(); i++)
		{
			if (!_pm->getVPlayerList()[i]->getIsDead())
			{
				if (_pm->getVPlayerList()[i]->getTurnState() == NOTMYTURN)
				{
					_pm->getVPlayerList()[i]->victoryBattle();
				}
			}
		}

		if (PLAYERDATA->getMonsterNumber() == 1)
		{
			PLAYERDATA->setSlimeDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 2)
		{
			PLAYERDATA->setFluffyBugDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 3)
		{
			PLAYERDATA->setFlytrapperDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 4)
		{
			PLAYERDATA->setBarbarianDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 5)
		{
			PLAYERDATA->setDevilBomberDie(true);
		}

		else if (SOUNDMANAGER->isPlaySound("battleMusic"))
		{
			SOUNDMANAGER->stop("battleMusic");
		}

		bool isEnd = false;
		
		for (int i = 0; i < _pm->getVPlayerList().size() - 1; i++)
		{
			if (!_pm->getVPlayerList()[i]->getIsDead())
			{
				if (i == 0)
				{
					isEnd = _pm->getVPlayerList()[i]->getIsVictory();
				}

				else
				{
					isEnd = isEnd && _pm->getVPlayerList()[i]->getIsVictory();
				}
			}
		}

		if (isEnd)
		{
			SCENEMANAGER->changeScene("던전");
		}
	}

	else if (_pm->getVPlayerList()[0]->getIsDead() && _pm->getVPlayerList()[1]->getIsDead() && _pm->getVPlayerList()[2]->getIsDead())
	{
		if (PLAYERDATA->getMonsterNumber() == 1)
		{
			PLAYERDATA->setSlimeDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 2)
		{
			PLAYERDATA->setFluffyBugDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 3)
		{
			PLAYERDATA->setFlytrapperDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 4)
		{
			PLAYERDATA->setBarbarianDie(true);
		}

		else if (PLAYERDATA->getMonsterNumber() == 5)
		{
			PLAYERDATA->setDevilBomberDie(true);
		}

		else if (SOUNDMANAGER->isPlaySound("battleMusic"))
		{
			SOUNDMANAGER->stop("battleMusic");
		}

		SCENEMANAGER->changeScene("던전");
	}

	else
	{
		if (_bsState == PLAYERTURN)
		{
			if (_playerTurnState == PLAYERTURNSTATE::START)
			{
				for (int i = 0; i < _pm->getVPlayerList().size(); i++)
				{
					if (!_pm->getVPlayerList()[i]->getIsDead())
					{
						_pm->getVPlayerList()[i]->setIsDefense(false);
					}
				}
				_playerTurnState = PLAYERTURNSTATE::UPDATE;
			}

			else if (_playerTurnState == PLAYERTURNSTATE::UPDATE)
			{
				setPlayerIndex();

				if (_userSelect == INIT)
				{
					if (_actionSelected != 0)
					{
						_actionSelected = 0;
					}

					_userSelect = SELECT;
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
						if (_pm->getVPlayerList()[_currentPlayerIndex]->getBullet() != NULL)
						{
							for (int i = 0; i < _pm->getVPlayerList()[_currentPlayerIndex]->getBullet()->getVBullet().size(); i++)
							{
								RECT bulletRc = _pm->getVPlayerList()[_currentPlayerIndex]->getBullet()->getVBullet()[i].rc;
								RECT enemyRc = _em->getVEnemyList()[_enemySelected]->getImg()->boundingBoxWithFrame();

								if (bulletRc.left < enemyRc.right - 30)
								{
									_pm->getVPlayerList()[_currentPlayerIndex]->setIsAttack(true);
									_pm->getVPlayerList()[_currentPlayerIndex]->getBullet()->removeBullet(i);
								}
							}
						}

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
							_playerTurnState = PLAYERTURNSTATE::START;
						}

						_userSelect = INIT;
					}
				}

				if (_userSelect == SKILL)
				{
					if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == NOTMYTURN)
					{
 						if (_currentPlayerIndex != 1)
						{
							selectEnemy();

							if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
							{
								_pm->getVPlayerList()[_currentPlayerIndex]->myTurnSkill(_enemySelected);
								_em->endSelect();
							}
						}

						else
						{
							_pm->getVPlayerList()[_currentPlayerIndex]->myTurnSkill(_enemySelected);
						}
					}

					else if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == MYTURN)
					{
						if (_pm->getVPlayerList()[_currentPlayerIndex]->getIsHeal())
						{
							for (int i = 0; i < _pm->getVPlayerList().size(); i++)
							{
								if (!_pm->getVPlayerList()[i]->getIsDead())
								{
									EFFECTMANAGER->addEffect(_pm->getVPlayerList()[i]->getPrevPos().x + 43, _pm->getVPlayerList()[i]->getPrevPos().y + 25, "bsLunar_skillEffect");
								}
							}

							_pm->getVPlayerList()[_currentPlayerIndex]->setIsHeal(false);
						}

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
							_playerTurnState = PLAYERTURNSTATE::START;
						}

						_userSelect = INIT;
					}
				}

				if (_userSelect == DEFENSE)
				{
					if (_pm->getVPlayerList()[_currentPlayerIndex]->getTurnState() == NOTMYTURN)
					{
						_pm->getVPlayerList()[_currentPlayerIndex]->myTurnDefense();
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
							_playerTurnState = PLAYERTURNSTATE::START;
						}

						_userSelect = INIT;
					}
				}

				if (_userSelect == GETAWAY)
				{
					if (_userSelect == GETAWAY)
					{
						if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
						{
							if (PLAYERDATA->getMonsterNumber() == 1)
							{
								PLAYERDATA->setSlimeDie(true);
							}
							if (PLAYERDATA->getMonsterNumber() == 2)
							{
								PLAYERDATA->setFluffyBugDie(true);
							}
							if (PLAYERDATA->getMonsterNumber() == 3)
							{
								PLAYERDATA->setFlytrapperDie(true);
							}
							if (PLAYERDATA->getMonsterNumber() == 4)
							{
								PLAYERDATA->setBarbarianDie(true);
							}
							if (PLAYERDATA->getMonsterNumber() == 5)
							{
								PLAYERDATA->setDevilBomberDie(true);
							}
							if (SOUNDMANAGER->isPlaySound("battleMusic"))
							{
								SOUNDMANAGER->stop("battleMusic");
							}
							SCENEMANAGER->changeScene("던전");
						}
					}
				}
			}
		}

		else if (_bsState == ENEMYTURN)
		{
			if (_enemyTurnState == ENEMYTURNSTATE::START)
			{
				setEnemyIndex();
				_enemyTurnState = ENEMYTURNSTATE::UPDATE;
			}

			else if (_enemyTurnState == ENEMYTURNSTATE::UPDATE)
			{
				if (_em->getVEnemyList()[_currentEnemyIndex]->getTurnState() == NOTMYTURN)
				{
					_playerSelected = 0;

					while (true)
					{
						_playerSelected = RND->getInt(_pm->getVPlayerList().size());

						if (!_pm->getVPlayerList()[_playerSelected]->getIsDead())
						{
							break;
						}
					}

					_em->getVEnemyList()[_currentEnemyIndex]->myTurnAttack(_playerSelected);
				}

				else if (_em->getVEnemyList()[_currentEnemyIndex]->getTurnState() == MYTURN)
				{
					if (!_em->getVEnemyList()[_currentEnemyIndex]->getIsDead())
					{
						if (_em->getVEnemyList()[_currentEnemyIndex]->getIsAttack())
						{
							_pm->getVPlayerList()[_playerSelected]->getDmg(_em->getVEnemyList()[_currentEnemyIndex]->getAtt());
							_em->getVEnemyList()[_currentEnemyIndex]->setIsAttack(false);
						}
					}
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
						_enemyTurnState = ENEMYTURNSTATE::START;
					}
				}
			}
		}
	}

	setUiImage();

	_pm->update();
	_em->update();

	EFFECTMANAGER->update();
}

void battleScene::render(void)
{
	_background->render(getMemDC());

	_pm->render();
	_em->render();

	EFFECTMANAGER->render(getMemDC());

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
			if (_currentPlayerIndex < 2)
			{
				_currentPlayerIndex++;
			}

			else
			{
				_currentPlayerIndex = 0;
				_bsState = ENEMYTURN;
				_playerTurnState = PLAYERTURNSTATE::START;
			}
		}

		else
		{
			break;
		}
	}
}

void battleScene::selectAction()
{
	if (_userSelect == SELECT)
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
			if (_enemySelected >= _em->getVEnemyList().size() - 1)
			{
				_enemySelected = 0;
			}

			else
			{
				_enemySelected++;
			}
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
					if (_enemySelected <= 0)
					{
						_enemySelected = 2;
					}

					else if (_enemySelected > 0)
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
					if (_enemySelected >= _em->getVEnemyList().size() - 1)
					{
						_enemySelected = 0;
					}

					else if (_enemySelected > 0)
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
		_uiGetaway = IMAGEMANAGER->findImage("bsUi_Getaway_Selected");
		_uiGetaway->setCenter(750, 50);
	}

	else
	{
		_uiGetaway = IMAGEMANAGER->findImage("bsUi_Getaway");
		_uiGetaway->setCenter(750, 50);
	}
}