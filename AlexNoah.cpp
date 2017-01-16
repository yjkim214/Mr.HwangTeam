#include "stdafx.h"
#include "AlexNoah.h"

#define ALEXNOAH_ATT		5
#define ALEXNOAH_DEF		5
#define ALEXNOAH_MAXHP		100
#define ALEXNOAH_MAXMP		20
#define ALEXNOAH_ANI_COUNT	10

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

	_playerImg = IMAGEMANAGER->findImage("bsPlayer_idle@2");
	_currentFrameX = 0;

	_isAttack = false;
	_isDead = false;

	_turnState = NOTMYTURN;

	_state = IDLE;

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

			if (_state == IDLE)
			{
				if (_currentFrameX > _playerImg->getMaxFrameX())
				{
					_currentFrameX = 0;
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

			if (_state == ATTACK)
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
						if (_delayCount >= 5)
						{
							_turnState = TURNEND;
							_playerImg = IMAGEMANAGER->findImage("bsPlayer_idle@2");
							_currentFrameX = 0;
							_state = IDLE;

							_isDelay = false;
						}
					}
				}
			}

			if (_state == SKILL)
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
						if (_delayCount >= 5)
						{
							_turnState = TURNEND;
							_playerImg = IMAGEMANAGER->findImage("bsPlayer_idle@2");
							_currentFrameX = 0;
							_state = IDLE;

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

void AlexNoah::myTurnAttack(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsPlayer_attack@2");
	_currentFrameX = 0;
	_state = ATTACK;
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

void AlexNoah::myTurnSkill(int enemyIndex)
{
	_turnState = MYTURN;
	_playerImg = IMAGEMANAGER->findImage("bsAlex_skill@2");
	_currentFrameX = 0;
	_state = SKILL;
	_destX = -50;

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

void AlexNoah::getDmg(int enemyAtt)
{
}