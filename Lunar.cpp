#include "stdafx.h"
#include "Lunar.h"

#define LUNAR_ATT		5
#define LUNAR_DEF		5
#define LUNAR_MAXHP		50
#define LUNAR_MAXMP		50
#define LUNAR_ANI_COUNT	5
#define DELAYTIME		10

HRESULT Lunar::init(void)
{
	_att = LUNAR_ATT;
	_def = LUNAR_DEF;

	_hp = LUNAR_MAXHP;
	_maxHp = LUNAR_MAXHP;
	_mp = LUNAR_MAXMP;
	_maxMp = LUNAR_MAXMP;

	_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");

	_uiImage = IMAGEMANAGER->findImage("bsLunar_Ui");
	_uiImage->setX(150);
	_uiImage->setY(5);

	_hpBar = new progressBar;
	_hpBar->init("bsHpbar_front", "bsBar_back", 190, 114, 75, 8);
	_hpBar->setGauge(_hp, _maxHp);

	_mpBar = new progressBar;
	_mpBar->init("bsMpbar_front", "bsBar_back", 190, 127, 75, 8);
	_mpBar->setGauge(_mp, _maxMp);

	_state = LUNAR_STATE::IDLE;

	moveX = 0;

	return S_OK;
}

void Lunar::release(void)
{
}

void Lunar::update(void)
{
	if(_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if(_countNotMyTurn % LUNAR_ANI_COUNT == 0)
		{
			_currentFrameX++;
			if(_state == LUNAR_STATE::IDLE)
			{
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if(_state == LUNAR_STATE::GETDMG)
			{
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							if(_hp <= 0)
							{
								_playerImg = IMAGEMANAGER->findImage("bsLunar_dead");
								_currentFrameX = 0;
								_state = LUNAR_STATE::DEAD;
							}

							else
							{
								_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
								_currentFrameX = 0;
								_state = LUNAR_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			if(_state == LUNAR_STATE::DEAD)
			{
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					_isDead = true;
				}
			}

			_countNotMyTurn = 0;
		}
	}

	else if(_turnState == MYTURN)
	{
		_countMyTurn++;
		if(_countMyTurn % LUNAR_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state == LUNAR_STATE::ATTACK)
			{
				if(_currentFrameX == 6)
				{
					_isAttack = true;
				}

				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;
							_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
							_currentFrameX = 0;
							_state = LUNAR_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if(_state == LUNAR_STATE::SKILL)
			{
				if(_currentFrameX == 5)
				{
					_isHeal = true;
				}

				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
							_currentFrameX = 0;
							_state = LUNAR_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if(_state == LUNAR_STATE::DEFENSE)
			{
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;

							_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
							_currentFrameX = 0;
							_state = LUNAR_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if(_state == LUNAR_STATE::VICTORY)
			{
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;
							_isVictory = true;
							_isDelay = false;
						}
					}
				}
			}

			if(_state == LUNAR_STATE::GETAWAY)
			{
				moveX += 5;
				if(_currentFrameX > _playerImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= DELAYTIME)
						{
							_turnState = TURNEND;
							_isVictory = true;
							_isDelay = false;
						}
					}
				}
			}
		}
	}

	else if(_turnState == TURNEND)
	{
		if(!_isVictory)
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

void Lunar::render(void)
{
	if(_turnState == NOTMYTURN || _turnState == TURNEND)
	{
		_playerImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
	}

	else if(_turnState == MYTURN)
	{
		if(_state == LUNAR_STATE::GETAWAY)
		{
			_playerImg->frameRender(getMemDC(), _destX + moveX, _destY, _currentFrameX, 0);
		}
		else
		{
			_playerImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
		}
	}

	_uiImage->render(getMemDC());

	_hpBar->render();
	_mpBar->render();
}

void Lunar::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_attack");
	_currentFrameX = 0;
	_state = LUNAR_STATE::ATTACK;
	_destX = WINSIZEX * 0.2f;

	if(enemyIndex == 0)
	{
		_destY = WINSIZEY * 0.3f;
	}

	else if(enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.5f;
	}

	else if(enemyIndex == 2)
	{
		_destY = WINSIZEY * 0.7f;
	}
}

void Lunar::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_skill");
	_currentFrameX = 0;
	_mp -= 4.0f;
	_mpBar->setGauge(_mp, _maxMp);
	_state = LUNAR_STATE::SKILL;
	_destX = _prevX;
	_destY = _prevY;
}

void Lunar::myTurnDefense()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_defense");
	_currentFrameX = 0;
	_state = LUNAR_STATE::DEFENSE;
	_isDefense = true;
	_destX = _prevX;
	_destY = _prevY;
}

void Lunar::victoryBattle()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_victory");
	_currentFrameX = 0;
	_state = LUNAR_STATE::VICTORY;
	_destX = _prevX;
	_destY = _prevY;
}

void Lunar::getaway()
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("lunarGetaway");
	_currentFrameX = 0;
	_state = LUNAR_STATE::GETAWAY;
	_destX = _prevX;
	_destY = _prevY;
}

void Lunar::getDmg(float enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsLunar_getdmg");
	_currentFrameX = 0;
	_state = LUNAR_STATE::GETDMG;

	if(!_isDefense)
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