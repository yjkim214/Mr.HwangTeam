#include "stdafx.h"
#include "bsFlytrapper.h"

#define FLYTRAPPER_ATT			4
#define FLYTRAPPER_DEF			4
#define FLYTRAPPER_MAXHP		100
#define FLYTRAPPER_MAXMP		10
#define FLYTRAPPER_ANICOUNT		10
#define FLYTRAPPER_DELAYTIME	4

HRESULT bsFlytrapper::init(void)
{
	_att = FLYTRAPPER_ATT;
	_def = FLYTRAPPER_DEF;

	_hp = FLYTRAPPER_MAXHP;
	_maxHp = FLYTRAPPER_MAXHP;
	_mp = FLYTRAPPER_MAXMP;
	_maxMp = FLYTRAPPER_MAXMP;

	_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");

	_state = FLYTRAPPER_STATE::IDLE;

	return S_OK;
}

void bsFlytrapper::release(void)
{
}

void bsFlytrapper::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % FLYTRAPPER_ANICOUNT == 0)
		{
			_currentFrameX++;

			if (_state == FLYTRAPPER_STATE::IDLE)
			{
				//애니메이션 무한정 반복
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			else if (_state == FLYTRAPPER_STATE::GETDMG)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= FLYTRAPPER_DELAYTIME)
						{
							_turnState = TURNEND;

							//데미지를 받았을 시
							if (_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("flytrapper_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state = FLYTRAPPER_STATE::DEAD;
							}

							else
							{
								_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
								_currentFrameX = 0;
								_state = FLYTRAPPER_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == FLYTRAPPER_STATE::DEAD)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= FLYTRAPPER_DELAYTIME)
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
		if (_countMyTurn % FLYTRAPPER_ANICOUNT == 0)
		{
			_currentFrameX++;
			if (_state == FLYTRAPPER_STATE::ATTACK)
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
						if (_delayCount >= FLYTRAPPER_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
							_currentFrameX = 0;
							_state = FLYTRAPPER_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == FLYTRAPPER_STATE::SKILL)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if (_currentFrameX == 6 || _currentFrameX == 7 || _currentFrameX == 8)
				{
					_isAttack = true;
				}

				//다시 대기 상태로 돌입
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= FLYTRAPPER_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
							_currentFrameX = 0;
							_state = FLYTRAPPER_STATE::IDLE;

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

void bsFlytrapper::render(void)
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


void bsFlytrapper::myTurn(int playerIndex)
{
	_turnState = MYTURN;
	int rndSkill = RND->getInt(3);
	if (rndSkill == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("flytrapper_skill");
		_state = FLYTRAPPER_STATE::SKILL;
	}
	else
	{
		_enemyImg = IMAGEMANAGER->findImage("flytrapper_attack");
		_state = FLYTRAPPER_STATE::ATTACK;
	}

	_currentFrameX = 0;
	//어택시 에너미 위치 잡아주는 코드
	_destX = WINSIZEX * 0.6f;
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

void bsFlytrapper::getDmg(float playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("flytrapper_getdmg");
	_currentFrameX = 0;
	_state = FLYTRAPPER_STATE::GETDMG;
	_hp -= (int)(playerAtt * playerAtt / _def) + 1;
	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}