#include "stdafx.h"
#include "Tempest.h"

#define Tempest_ANI_COUNT	5
#define DELAYTIME			20

HRESULT Tempest::init(void)
{
	_att = PLAYERDATA->getTematt();
	_def = PLAYERDATA->getTemdef();

	_hp = PLAYERDATA->getTemcurrenthp();
	_maxHp = PLAYERDATA->getTemMaxhp();
	_mp = PLAYERDATA->getTemcurrentmp();
	_maxMp = PLAYERDATA->getTemMaxmp();

	_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");

	_bullet = new bullet;
	_bullet->init("arrow", 1, 800);

	_uiImage = IMAGEMANAGER->findImage("bsTempest_Ui");
	_uiImage->setX(300);
	_uiImage->setY(5);

	_hpBar = new progressBar;
	_hpBar->init("bsHpbar_front", "bsBar_back", 340, 101, 75, 8);
	_hpBar->setGauge(_hp, _maxHp);
	
	_mpBar = new progressBar;
	_mpBar->init("bsMpbar_front", "bsBar_back", 340, 114, 75, 8);
	_mpBar->setGauge(_mp, _maxMp);

	_state = TEMPEST_STATE::IDLE;

	return S_OK;
}

void Tempest::release(void)
{
}

void Tempest::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % Tempest_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == TEMPEST_STATE::IDLE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			else if (_state == TEMPEST_STATE::GETDMG)
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
								_playerImg = IMAGEMANAGER->findImage("bsTempest_dead");
								_currentFrameX = 0;
								_state = TEMPEST_STATE::DEAD;
							}

							else
							{
								_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");
								_currentFrameX = 0;
								_state = TEMPEST_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == TEMPEST_STATE::DEAD)
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
		if (_countMyTurn % Tempest_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == TEMPEST_STATE::ATTACK)
			{
				if (_currentFrameX == 3)
				{
					_bullet->fire(_destX + 50, _destY + 100, PI, 20.0f);
				}

				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_bullet->getVBullet().size() == 0)
					{
						if (_isDelay)
						{
							_delayCount++;
							if (_delayCount >= DELAYTIME)
							{
								_turnState = TURNEND;
								_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");
								_currentFrameX = 0;
								_state = TEMPEST_STATE::IDLE;

								_isDelay = false;
							}
						}
					}
				}
			}

			else if (_state == TEMPEST_STATE::SKILL)
			{
				if (_currentFrameX == 7)
				{
					EFFECTMANAGER->addEffect(_destX - 248, _destY + 75, "bsTempest_skilEffect");
				}

				if (_currentFrameX == 7 || _currentFrameX == 9 || _currentFrameX == 11)
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

							_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");
							_currentFrameX = 0;
							_state = TEMPEST_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == TEMPEST_STATE::DEFENSE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");
							_currentFrameX = 0;
							_state = TEMPEST_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == TEMPEST_STATE::VICTORY)
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

			else if(_state == TEMPEST_STATE::GETAWAY)
			{
				_destX += 10;
				if (_destX > 800)
				{
					_isGetaway = true;
				}

				if (_currentFrameX > _playerImg->getMaxFrameX())
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

	_bullet->update();

	_hpBar->setGauge(_hp, _maxHp);
	_mpBar->setGauge(_mp, _maxMp);

	_hpBar->update();
	_mpBar->update();
}

void Tempest::render(void)
{
	if (_turnState == NOTMYTURN || _turnState == TURNEND)
	{
		_playerImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
	}

	else if (_turnState == MYTURN)
	{
		_playerImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
	}

	_bullet->render();

	_uiImage->render(getMemDC());
	
	_hpBar->render();
	_mpBar->render();
}

void Tempest::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsTempest_attack");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::ATTACK;
	_destX = WINSIZEX * 0.5f;

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

void Tempest::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsTempest_skill");
	_currentFrameX = 0;
	_mp -= 4.0f;
	_mpBar->setGauge(_mp, _maxMp);
	_state = TEMPEST_STATE::SKILL;
	_destX = WINSIZEX * 0.5f;

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

void Tempest::myTurnDefense()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsTempest_defense");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::DEFENSE;
	_isDefense = true;
	_destX = _prevX;
	_destY = _prevY;
}

void Tempest::victoryBattle()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsTempest_victory");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::VICTORY;
	_destX = _prevX;
	_destY = _prevY;
}

void Tempest::getaway()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("tempestGetaway");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::GETAWAY;
	_destX = _prevX;
	_destY = _prevY;
}

void Tempest::getDmg(float enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsTempest_getdmg");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::GETDMG;

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

	_hpBar->setGauge(_hp, _maxHp);

	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _playerImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _playerImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}

void Tempest::saveData()
{
	PLAYERDATA->setTematt(_att);
	PLAYERDATA->setTemdef(_def);
	if (_isDead)
	{
		PLAYERDATA->setTemcurrenthp(1);
	}
	else
	{
		PLAYERDATA->setTemcurrenthp(_hp);
	}
	PLAYERDATA->setTemcurrentmp(_mp);
	PLAYERDATA->setTemMaxhp(_maxHp);
	PLAYERDATA->setTemMaxmp(_maxMp);
}
