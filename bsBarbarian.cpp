#include "stdafx.h"
#include "bsBarbarian.h"

#define BARBARIAN_ATT		5
#define BARBARIAN_DEF		5
#define BARBARIAN_MAXHP		50
#define BARBARIAN_MAXMP		10
#define BARBARIAN_ANICOUNT	10
#define BARBARIAN_DELAYTIME	5

HRESULT bsBarbarian::init(void)
{
	_att = BARBARIAN_ATT;
	_def = BARBARIAN_DEF;

	_hp = BARBARIAN_MAXHP;
	_maxHp = BARBARIAN_MAXHP;
	_mp = BARBARIAN_MAXMP;
	_maxMp = BARBARIAN_MAXMP;

	_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");

	_state = BARBARIAN_STATE::IDLE;

	return S_OK;
}

void bsBarbarian::release(void)
{
}

void bsBarbarian::update(void)
{
	if(_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if(_countNotMyTurn % BARBARIAN_ANICOUNT == 0)
		{
			_currentFrameX++;

			if(_state == BARBARIAN_STATE::IDLE)
			{
				//애니메이션 무한정 반복
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			else if(_state == BARBARIAN_STATE::GETDMG)
			{
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= BARBARIAN_DELAYTIME)
						{
							_turnState = TURNEND;

							//데미지를 받았을 시
							if(_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("barbarian_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state = BARBARIAN_STATE::DEAD;
							}
							else
							{
								_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");
								_currentFrameX = 0;
								_state = BARBARIAN_STATE::IDLE;
							}

							_isDelay = false;
						}
					}
				}
			}

			else if(_state == BARBARIAN_STATE::DEAD)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= BARBARIAN_DELAYTIME)
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

	else if(_turnState == MYTURN)
	{
		_countMyTurn++;
		if(_countMyTurn % BARBARIAN_ANICOUNT == 0)
		{
			_currentFrameX++;
			if(_state == BARBARIAN_STATE::ATTACK)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if(_currentFrameX == 6)
				{
					_isAttack = true;
				}
				//다시 대기 상태로 돌입
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= BARBARIAN_DELAYTIME)
						{
							_turnState = TURNEND;

							_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");
							_currentFrameX = 0;
							_state = BARBARIAN_STATE::IDLE;

							_isDelay = false;
						}
					}
				}
			}

			_countMyTurn = 0;
		}
	}

	else if(_turnState == TURNEND)
	{
		_isDelay = true;
		_delayCount = 0;
		_turnState = NOTMYTURN;
	}
}

void bsBarbarian::render(void)
{
	if(!_isDead)
	{
		if(_turnState == MYTURN)
		{
			_enemyImg->frameRender(getMemDC(), _destX, _destY, _currentFrameX, 0);
		}

		else if(_turnState == NOTMYTURN)
		{
			if(_isSelected)
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

void bsBarbarian::myTurn(int playerIndex)
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("barbarian_attack");
	_currentFrameX = 0;
	_state = BARBARIAN_STATE::ATTACK;
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

void bsBarbarian::getDmg(float playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("barbarian_getdmg");
	_currentFrameX = 0;
	_state = BARBARIAN_STATE::GETDMG;
	_hp -= (int)(playerAtt * playerAtt / _def) + 1;
	int rndX = RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65);
	int rndY = RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight());
	EFFECTMANAGER->addEffect(rndX, rndY, "bsEffect_attack");
}