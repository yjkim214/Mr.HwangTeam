#include "stdafx.h"
#include "bsFluffyBug.h"

#define FluffyBug_ATT		3
#define FluffyBug_DEF		3
#define FluffyBug_MAXHP		50
#define FluffyBug_MAXMP		10
#define FluffyBug_ANI_COUNT	10

HRESULT bsFluffyBug::init(void)
{
	_att = FluffyBug_ATT;
	_def = FluffyBug_DEF;

	_hp = FluffyBug_MAXHP;
	_maxHp = FluffyBug_MAXHP;
	_mp = FluffyBug_MAXMP;
	_maxMp = FluffyBug_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isSelected = true;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("fluffyBug_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state2 = IDLE2;

	return S_OK;
}

void bsFluffyBug::release(void)
{
}

void bsFluffyBug::update(void)
{
	if(_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if(_countNotMyTurn % FluffyBug_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state2 == IDLE2)
			{
				//애니메이션 무한정 반복
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if(_state2 == GETDMG2)
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
								_enemyImg = IMAGEMANAGER->findImage("fluffyBug_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state2 = DEAD2;
							}
							else
							{
								_enemyImg = IMAGEMANAGER->findImage("fluffyBug_idle");
								_currentFrameX = 0;
								_state2 = IDLE2;
							}
							_isDelay = false;
						}
					}
				}
			}

			if(_state2 == DEAD2)
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
		if(_countMyTurn % FluffyBug_ANI_COUNT == 0)
		{
			_currentFrameX++;
			if(_state2 == ATTACK2)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if(_currentFrameX == 5)
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
							_enemyImg = IMAGEMANAGER->findImage("fluffyBug_idle");
							_currentFrameX = 0;
							_state2 = IDLE2;

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

void bsFluffyBug::render(void)
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

void bsFluffyBug::myTurnAttack(int playerIndex)
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("fluffyBug_attack");
	_currentFrameX = 0;
	_state2 = ATTACK2;
	//어택시 에너미 위치 잡아주는 코드
	_destX = WINSIZEX * 0.5f;
	if(playerIndex == 0)
	{
		_destY = WINSIZEY * 0.1f;
	}

	else if (playerIndex == 1)
	{
		_destY = WINSIZEY * 0.4f;
	}

	else
	{
		_destY = WINSIZEY * 0.7f;
	}
}

//void bsFluffyBug::myTurn()
//{
//	_turnState = MYTURN;
//	_enemyImg = IMAGEMANAGER->findImage("fluffyBug_attack");
//	_currentFrameX = 0;
//	_state2 = ATTACK2;
//}

void bsFluffyBug::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("fluffyBug_getdmg");
	_currentFrameX = 0;
	_state2 = GETDMG2;
	_hp -= playerAtt * playerAtt / _def + 1;
	EFFECTMANAGER->addEffect(RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65), RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight()), "bsEffect_attack");
}