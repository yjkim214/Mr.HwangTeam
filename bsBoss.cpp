#include "stdafx.h"
#include "bsBoss.h"

#define BOSS_ATT		20
#define BOSS_DEF		20
#define BOSS_MAXHP		1000
#define BOSS_MAXMP		1000
#define BOSS_ANICOUNT	10
#define BOSS_DELAYTIME	5

HRESULT bsBoss::init(void)
{
	_att = BOSS_ATT;
	_def = BOSS_DEF;

	_hp = BOSS_MAXHP;
	_maxHp = BOSS_MAXHP;
	_mp = BOSS_MAXMP;
	_maxMp = BOSS_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isSelected = true;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("bsBoss_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state = BOSS_STATE::IDLE;

	return S_OK;
}

void bsBoss::release(void)
{
}

void bsBoss::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % BOSS_ANICOUNT == 0)
		{
			_currentFrameX++;

			if (_state == BOSS_STATE::IDLE)
			{
				//애니메이션 무한정 반복
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if (_state == BOSS_STATE::GETDMG)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BOSS_DELAYTIME)
						{
							_turnState = TURNEND;

							//데미지를 받았을 시
							if (_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("bsBoss_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state = BOSS_STATE::DEAD;
							}

							else
							{
								_enemyImg = IMAGEMANAGER->findImage("bsBoss_idle");
								_currentFrameX = 0;
								_state = BOSS_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			if (_state == BOSS_STATE::DEAD)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BOSS_DELAYTIME)
						{
							_turnState = TURNEND;
							_isDead = true;
							_isDelay = false;
						}
					}
				}
			}

			_countNotMyTurn = 0;
		}
	}

	else if (_turnState == MYTURN)
	{
		_countMyTurn++;
		if (_countMyTurn % BOSS_ANICOUNT == 0)
		{
			_currentFrameX++;
			if (_state == BOSS_STATE::ATTACK)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if (_currentFrameX == 4)
				{
					_isAttack = true;
				}

				//다시 대기 상태로 돌입
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BOSS_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("bsBoss_idle");
							_currentFrameX = 0;
							_state = BOSS_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == BOSS_STATE::SKILL01)
			{
				if (_currentFrameX == 8 || _currentFrameX == 9 || _currentFrameX == 10)
				{
					_isAttack = true;
				}

				else if (_currentFrameX == 11)
				{
					_destX = WINSIZEX * 0.8f;
				}

				else if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BOSS_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("bsBoss_idle");
							_currentFrameX = 0;
							_state = BOSS_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == BOSS_STATE::SKILL02)
			{
				if (_currentFrameX == 4)
				{
					EFFECTMANAGER->addEffect(WINSIZEX * 0.7f, _destY, "bsBoss_skill02_Effect");
				}

				else if (_currentFrameX == 5 || _currentFrameX == 7 || _currentFrameX == 9)
				{
					_isAttack = true;
				}

				else if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BOSS_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("bsBoss_idle");
							_currentFrameX = 0;
							_state = BOSS_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			_countMyTurn = 0;
		}
	}

	else if (_turnState == TURNEND)
	{
		_isDelay = true;
		_delayCount = 0;
		_turnState = NOTMYTURN;
	}
}

void bsBoss::render(void)
{
	if (!_isDead)
	{
		if (_turnState == MYTURN)
		{
			_enemyImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
		}

		else if (_turnState == NOTMYTURN)
		{
			if (_isSelected)
			{
				_enemyImg->frameRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0);
			}

			else
			{
				_enemyImg->frameAlphaRender(getMemDC(), _prevX, _prevY, _currentFrameX, 0, 100);
			}
		}
	}
}

void bsBoss::myTurnAttack(int playerIndex)
{
	_turnState = MYTURN;

	int rndSkill = RND->getInt(4);
	if (rndSkill == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("bsBoss_skill01");
		_state = BOSS_STATE::SKILL01;

		//어택시 에너미 위치 잡아주는 코드
		_destX = WINSIZEX * 0.5f;
		if (playerIndex == 0)
		{
			_destY = WINSIZEY * 0.3f;
		}

		else if (playerIndex == 1)
		{
			_destY = WINSIZEY * 0.5f;
		}

		else
		{
			_destY = WINSIZEY * 0.7f;
		}
	}

	else if (rndSkill == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("bsBoss_skill02");
		_state = BOSS_STATE::SKILL02;

		//어택시 에너미 위치 잡아주는 코드
		_destX = WINSIZEX * 0.5f;
		if (playerIndex == 0)
		{
			_destY = WINSIZEY * 0.3f;
		}

		else if (playerIndex == 1)
		{
			_destY = WINSIZEY * 0.5f;
		}

		else
		{
			_destY = WINSIZEY * 0.7f;
		}
	}

	else
	{
		_enemyImg = IMAGEMANAGER->findImage("bsBoss_attack");
		_state = BOSS_STATE::ATTACK;

		//어택시 에너미 위치 잡아주는 코드
		_destX = WINSIZEX * 0.5f;
		if (playerIndex == 0)
		{
			_destY = WINSIZEY * 0.3f;
		}

		else if (playerIndex == 1)
		{
			_destY = WINSIZEY * 0.5f;
		}

		else
		{
			_destY = WINSIZEY * 0.7f;
		}
	}

	_currentFrameX = 0;
}

void bsBoss::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("bsBoss_getdmg");
	_currentFrameX = 0;
	_state = BOSS_STATE::GETDMG;
	_hp -= playerAtt * playerAtt / _def + 1;
	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}