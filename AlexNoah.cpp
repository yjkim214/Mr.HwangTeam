#include "stdafx.h"
#include "AlexNoah.h"

#define ALEXNOAH_ANI_COUNT	5
#define DELAYTIME			10

HRESULT AlexNoah::init(void)
{
	_att = PLAYERDATA->getAlexatt();
	_def = PLAYERDATA->getAlexdef();

	_hp = PLAYERDATA->getAlexcurrenthp();
	_maxHp = PLAYERDATA->getAlexMaxhp();
	_mp = PLAYERDATA->getAlexcurrentmp();
	_maxMp = PLAYERDATA->getAlexMaxmp();

	_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");

	_uiImage = IMAGEMANAGER->findImage("bsAlex_Ui");
	_uiImage->setX(0);
	_uiImage->setY(5);

	_hpBar = new progressBar;
	_hpBar->init("bsHpbar_front", "bsBar_back", 40, 114, 75, 8);
	_hpBar->setGauge(_hp, _maxHp);

	_mpBar = new progressBar;
	_mpBar->init("bsMpbar_front", "bsBar_back", 40, 127, 75, 8);
	_mpBar->setGauge(_mp, _maxMp);

	_state = ALEXNOAH_STATE::IDLE;

	return S_OK;
}

void AlexNoah::release(void)
{
}

void AlexNoah::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % ALEXNOAH_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == ALEXNOAH_STATE::IDLE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			else if (_state == ALEXNOAH_STATE::GETDMG)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							if (_hp <= 0)
							{
								_playerImg = IMAGEMANAGER->findImage("bsAlex_dead@2");
								_currentFrameX = 0;
								_state = ALEXNOAH_STATE::DEAD;
							}

							else
							{
								_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
								_currentFrameX = 0;
								_state = ALEXNOAH_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == ALEXNOAH_STATE::DEAD)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					_isDead = true;
				}
			}

			_countNotMyTurn = 0;
		}
	}

	else if (_turnState == MYTURN)
	{
		_countMyTurn++;

		if (_countMyTurn % ALEXNOAH_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == ALEXNOAH_STATE::ATTACK)
			{
				if (_currentFrameX == 4)
				{
					_isAttack = true;
				}

				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
							_currentFrameX = 0;
							_state = ALEXNOAH_STATE::IDLE;
							
							_turnState = TURNEND;
							_isDelay = false;
						}
					}
				}
			}

			else if (_state == ALEXNOAH_STATE::SKILL)
			{
				if (_currentFrameX == 2 || _currentFrameX == 9 || _currentFrameX == 15 || _currentFrameX == 19 || _currentFrameX == 20 || _currentFrameX == 21 || _currentFrameX == 22 || _currentFrameX == 23 || _currentFrameX == 24)
				{
					_isAttack = true;
				}

				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;
							
							_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
							_currentFrameX = 0;
							_state = ALEXNOAH_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == ALEXNOAH_STATE::DEFENSE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
							_currentFrameX = 0;
							_state = ALEXNOAH_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == ALEXNOAH_STATE::VICTORY)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;
							_isVictory = true;
							_isDelay = false;
						}
					}
				}
			}

			if(_state == ALEXNOAH_STATE::GETAWAY)
			{
				_destX += 10;
				if (_destX > 800)
				{
					_isGetaway = true;
				}

				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}
		}
	}

	else if (_turnState == TURNEND)
	{
		if (!_isVictory)
		{
			_isDelay = true;
			_delayCount = 0;
			_turnState = NOTMYTURN;
		}
	}

	_hpBar->setGauge(_hp, _maxHp);
	_mpBar->setGauge(_mp, _maxMp);

	_hpBar->update();
	_mpBar->update();
}

void AlexNoah::render(void)
{
	if (_turnState == NOTMYTURN || _turnState == TURNEND)
	{
		_playerImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
	}

	else if (_turnState == MYTURN)
	{
		_playerImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
	}

	_uiImage->render(getMemDC());
	
	_hpBar->render();
	_mpBar->render();
}

void AlexNoah::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_attack@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::ATTACK;
	_destX = WINSIZEX * 0.2f;

	if (enemyIndex == 0)
	{
		_destY = WINSIZEY * 0.3f;
	}

	else if (enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.5f;
	}

	else if (enemyIndex == 2)
	{
		_destY = WINSIZEY * 0.7f;
	}
}

void AlexNoah::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_skill@2");
	_currentFrameX = 0;
	_mp -= 4.0f;
	_state = ALEXNOAH_STATE::SKILL;
	_destX = 30;
	if (enemyIndex == 0)
	{
		_destY = WINSIZEY * 0.3f;
	}

	else if (enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.5f;
	}

	else if (enemyIndex == 2)
	{
		_destY = WINSIZEY * 0.7f;
	}
}

void AlexNoah::myTurnDefense()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_defense@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::DEFENSE;
	_isDefense = true;
	_destX = _prevX;
	_destY = _prevY;
}

void AlexNoah::victoryBattle()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_victory@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::VICTORY;
	_destX = _prevX;
	_destY = _prevY;
}

void AlexNoah::getaway()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("alexGetaway");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::GETAWAY;
	_destX = _prevX;
	_destY = _prevY;
}

void AlexNoah::getDmg(float enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsAlex_getdmg@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::GETDMG;

	if (!_isDefense)
	{
		int damage = (int)(enemyAtt * enemyAtt / _def) + 1.0f;
		_hp -= damage;
	}

	else
	{
		int damage = (int)(enemyAtt * enemyAtt / (_def * 2)) + 1.0f;
		_hp -= damage;
	}

	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _playerImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _playerImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}

void AlexNoah::saveData()
{
	PLAYERDATA->setAlexatt(_att);
	PLAYERDATA->setAlexdef(_def);
	if (_isDead)
	{
		PLAYERDATA->setAlexcurrenthp(1);
	}
	else
	{
		PLAYERDATA->setAlexcurrenthp(_hp);
	}
	PLAYERDATA->setAlexcurrentmp(_mp);
	PLAYERDATA->setAlexMaxhp(_maxHp);
	PLAYERDATA->setAlexMaxmp(_maxMp);
}