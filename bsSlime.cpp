#include "stdafx.h"
#include "bsSlime.h"

#define SLIME_ATT		2
#define SLIME_DEF		2
#define SLIME_MAXHP		50
#define SLIME_MAXMP		10
#define SLIME_ANICOUNT	10
#define SLIME_DELAYTIME	5

HRESULT bsSlime::init(void)
{
	_att = SLIME_ATT;
	_def = SLIME_DEF;

	_hp = SLIME_MAXHP;
	_maxHp = SLIME_MAXHP;
	_mp = SLIME_MAXMP;
	_maxMp = SLIME_MAXMP;

	_xp = 5;

	_enemyImg = IMAGEMANAGER->findImage("slime_idle");

	_state = SLIME_STATE::IDLE;

	return S_OK;
}

void bsSlime::release(void)
{
}

void bsSlime::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if (_countNotMyTurn % SLIME_ANICOUNT == 0)
		{
			_currentFrameX++;

			if (_state == SLIME_STATE::IDLE)
			{
				//애니메이션 무한정 반복
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			else if (_state == SLIME_STATE::GETDMG)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= SLIME_DELAYTIME)
						{
							_turnState = TURNEND;

							//데미지를 받았을 시
							if (_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("slime_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state = SLIME_STATE::DEAD;
							}

							else
							{
								_enemyImg = IMAGEMANAGER->findImage("slime_idle");
								_currentFrameX = 0;
								_state = SLIME_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			else if (_state == SLIME_STATE::DEAD)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= SLIME_DELAYTIME)
						{
							_turnState = TURNEND;

							_isDead = true;
							_isGetXp = true;
							
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
		if (_countMyTurn % SLIME_ANICOUNT == 0)
		{
			_currentFrameX++;
			if (_state == SLIME_STATE::ATTACK)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if (_currentFrameX == 3)
				{
					_isAttack = true;
				}
				//다시 대기 상태로 돌입
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= SLIME_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("slime_idle");
							_currentFrameX = 0;
							_state = SLIME_STATE::IDLE;

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

void bsSlime::render(void)
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

void bsSlime::myTurn(int playerIndex)
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("slime_attack");
	_currentFrameX = 0;
	_state = SLIME_STATE::ATTACK;
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

void bsSlime::getDmg(float playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("slime_getdmg");
	_currentFrameX = 0;
	_state = SLIME_STATE::GETDMG;
	_hp -= (int)(playerAtt * playerAtt / _def) + 1;
	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}