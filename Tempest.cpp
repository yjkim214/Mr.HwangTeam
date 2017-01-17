#include "stdafx.h"
#include "Tempest.h"

#define Tempest_ATT			10
#define Tempest_DEF			5
#define Tempest_MAXHP		75
#define Tempest_MAXMP		20
#define Tempest_ANI_COUNT	5
#define DELAYTIME			10

HRESULT Tempest::init(void)
{
	_att = Tempest_ATT;
	_def = Tempest_DEF;

	_hp = Tempest_MAXHP;
	_maxHp = Tempest_MAXHP;
	_mp = Tempest_MAXMP;
	_maxMp = Tempest_MAXMP;

	_playerImg = IMAGEMANAGER->findImage("bsTempest_idle");

	_state = TEMPEST_STATE::IDLE;

	_bullet = new bullet;
	_bullet->init("arrow", 1, 800);

	return S_OK;
}

void Tempest::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
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

			if (_state == TEMPEST_STATE::GETDMG)
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

			if (_state == TEMPEST_STATE::DEAD)
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

			if (_state == TEMPEST_STATE::SKILL)
			{
				if (_currentFrameX == 7)
				{
					EFFECTMANAGER->addEffect(_destX - 248, _destY + 75, "bsTempest_skilEffect");
				}

				if (_currentFrameX == 11)
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

			if (_state == TEMPEST_STATE::DEFENSE)
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

			if (_state == TEMPEST_STATE::VICTORY)
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
		}
	}

	else if (_turnState == TURNEND)
	{
		_isDelay = true;
		_delayCount = 0;
		_turnState = NOTMYTURN;
	}

	_bullet->update();
}

void Tempest::render(void)
{
	if (_turnState == NOTMYTURN)
	{
		_playerImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
	}

	else if (_turnState == MYTURN)
	{
		_playerImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
	}

	_bullet->render();
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
		_destY = WINSIZEY * 0.1f;
	}

	else if (enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.4f;
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
	_state = TEMPEST_STATE::SKILL;
	_destX = WINSIZEX * 0.5f;

	if (enemyIndex == 0)
	{
		_destY = WINSIZEY * 0.1f;
	}

	else if (enemyIndex == 1)
	{
		_destY = WINSIZEY * 0.4f;
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

void Tempest::getDmg(int enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsTempest_getdmg");
	_currentFrameX = 0;
	_state = TEMPEST_STATE::GETDMG;

	if (_isDefense)
	{
		_hp -= (enemyAtt * enemyAtt / _def + 1);
	}

	else
	{
		_hp -= (enemyAtt * enemyAtt / (_def * 2) + 1);
	}

	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _playerImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _playerImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}