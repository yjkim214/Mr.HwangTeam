#include "stdafx.h"
#include "Lunar.h"

#define LUNAR_ATT		5
#define LUNAR_DEF		5
#define LUNAR_MAXHP		2
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

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_isAttack = false;
	_isHeal = false;
	_isDead = false;

	_turnState = NOTMYTURN;

	_bullet = NULL;

	_state = LUNAR_STATE::IDLE;

	return S_OK;
}

void Lunar::release(void)
{
}

void Lunar::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % LUNAR_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == LUNAR_STATE::IDLE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if (_state == LUNAR_STATE::GETDMG)
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

			if (_state == LUNAR_STATE::DEAD)
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

		if (_countMyTurn % LUNAR_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == LUNAR_STATE::ATTACK)
			{
				if (_currentFrameX == 6)
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
							_playerImg = IMAGEMANAGER->findImage("bsLunar_idle");
							_currentFrameX = 0;
							_state = LUNAR_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if (_state == LUNAR_STATE::SKILL)
			{
				if (_currentFrameX == 5)
				{
					_isHeal = true;
				}

				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= DELAYTIME)
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
		}
	}

	else if (_turnState == TURNEND)
	{
		_isDelay = true;
		_delayCount = 0;
		_turnState = NOTMYTURN;
	}
}

void Lunar::render(void)
{
	if (_turnState == NOTMYTURN)
	{
		_playerImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
	}

	if (_turnState == MYTURN)
	{
		_playerImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
	}
}

void Lunar::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_attack");
	_currentFrameX = 0;
	_state = LUNAR_STATE::ATTACK;
	_destX = WINSIZEX * 0.3f;

	if (enemyIndex == 0)
	{
		_destY = 0;
	}

	else if (enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.25f;
	}

	else if (enemyIndex == 2)
	{
		_destY = WINSIZEY * 0.5f;
	}
}

void Lunar::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsLunar_skill");
	_currentFrameX = 0;
	_state = LUNAR_STATE::SKILL;
	_destX = _prevX;
	_destY = _prevY;
}

void Lunar::getDmg(int enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsLunar_getdmg");
	_currentFrameX = 0;
	_state = LUNAR_STATE::GETDMG;
	_hp -= (enemyAtt * enemyAtt / _def + 1);
}