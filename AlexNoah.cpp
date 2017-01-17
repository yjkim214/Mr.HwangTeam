#include "stdafx.h"
#include "AlexNoah.h"

#define ALEXNOAH_ATT		5
#define ALEXNOAH_DEF		5
#define ALEXNOAH_MAXHP		100
#define ALEXNOAH_MAXMP		20
#define ALEXNOAH_ANI_COUNT	5
#define DELAYTIME			10

HRESULT AlexNoah::init(void)
{
	_att = ALEXNOAH_ATT;
	_def = ALEXNOAH_DEF;

	_hp = ALEXNOAH_MAXHP;
	_maxHp = ALEXNOAH_MAXHP;
	_mp = ALEXNOAH_MAXMP;
	_maxMp = ALEXNOAH_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
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

			if (_state == ALEXNOAH_STATE::GETDMG)
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

			if (_state == ALEXNOAH_STATE::DEAD)
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
							_turnState = TURNEND;
							_playerImg = IMAGEMANAGER->findImage("bsAlex_idle@2");
							_currentFrameX = 0;
							_state = ALEXNOAH_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if (_state == ALEXNOAH_STATE::SKILL)
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
		}
	}

	else if (_turnState == TURNEND)
	{
		_isDelay = true;
		_delayCount = 0;
		_turnState = NOTMYTURN;
	}
}

void AlexNoah::render(void)
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

void AlexNoah::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_attack@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::ATTACK;
	_destX = WINSIZEX * 0.2f;

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

void AlexNoah::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_skill@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::SKILL;
	_destX = 35;

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

void AlexNoah::getDmg(int enemyAtt)
{
	_playerImg = IMAGEMANAGER->findImage("bsAlex_getdmg@2");
	_currentFrameX = 0;
	_state = ALEXNOAH_STATE::GETDMG;
	_hp -= (enemyAtt * enemyAtt / _def + 1);
	EFFECTMANAGER->addEffect(RND->getFromIntTo(_prevX + 30, _prevX + _playerImg->getFrameWidth() - 65), RND->getFromIntTo(_prevY + 75, _prevY + _playerImg->getFrameHeight()), "bsEffect_attack");
}