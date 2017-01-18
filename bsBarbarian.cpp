#include "stdafx.h"
#include "bsBarbarian.h"

#define Barbarian_ATT		5
#define Barbarian_DEF		5
#define Barbarian_MAXHP		50
#define Barbarian_MAXMP		10
#define Barbarian_ANI_COUNT	10

HRESULT bsBarbarian::init(void)
{
	_att = Barbarian_ATT;
	_def = Barbarian_DEF;

	_hp = Barbarian_MAXHP;
	_maxHp = Barbarian_MAXHP;
	_mp = Barbarian_MAXMP;
	_maxMp = Barbarian_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isDead = false;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state4 = IDLE4;

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
		if(_countNotMyTurn % Barbarian_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state4 == IDLE4)
			{
				//애니메이션 무한정 반복
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if(_state4 == GETDMG4)
			{
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= 5)
						{
							_turnState = TURNEND;

							//데미지를 받았을 시
							if(_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("barbarian_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state4 = DEAD4;
							}
							else
							{
								_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");
								_currentFrameX = 0;
								_state4 = IDLE4;
							}
							_isDelay = false;
						}
					}
				}
			}

			if(_state4 == DEAD4)
			{
				if(_currentFrameX > _enemyImg->getMaxFrameX())
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
		if(_countMyTurn % Barbarian_ANI_COUNT == 0)
		{
			_currentFrameX++;
			if(_state4 == ATTACK4)
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
						if(_delayCount >= 5)
						{
							_turnState = TURNEND;
							_enemyImg = IMAGEMANAGER->findImage("barbarian_idle");
							_currentFrameX = 0;
							_state4 = IDLE4;

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

void bsBarbarian::myTurnAttack(int playerIndex)
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("barbarian_attack");
	_currentFrameX = 0;
	_state4 = ATTACK4;
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

void bsBarbarian::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("barbarian_getdmg");
	_currentFrameX = 0;
	_state4 = GETDMG4;
	_hp -= playerAtt * playerAtt / _def + 1;
	EFFECTMANAGER->addEffect(RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65), RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight()), "bsEffect_attack");
}