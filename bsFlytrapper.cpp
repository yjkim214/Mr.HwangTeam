#include "stdafx.h"
#include "bsFlytrapper.h"

#define Flytrapper_ATT		4
#define Flytrapper_DEF		4
#define Flytrapper_MAXHP		50
#define Flytrapper_MAXMP		10
#define Flytrapper_ANI_COUNT	10

HRESULT bsFlytrapper::init(void)
{
	_att = Flytrapper_ATT;
	_def = Flytrapper_DEF;

	_hp = Flytrapper_MAXHP;
	_maxHp = Flytrapper_MAXHP;
	_mp = Flytrapper_MAXMP;
	_maxMp = Flytrapper_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isSelected = true;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state3 = IDLE3;

	return S_OK;
}

void bsFlytrapper::release(void)
{
}

void bsFlytrapper::update(void)
{
	if(_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if(_countNotMyTurn % Flytrapper_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state3 == IDLE3)
			{
				//애니메이션 무한정 반복
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if(_state3 == GETDMG3)
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
								_enemyImg = IMAGEMANAGER->findImage("flytrapper_dead");
								_currentFrameX = 0;
								//hp가 바닥이면 죽은 상태로 바꿈
								_state3 = DEAD3;
							}
							else
							{
								_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
								_currentFrameX = 0;
								_state3 = IDLE3;
							}
							_isDelay = false;
						}
					}
				}
			}

			if(_state3 == DEAD3)
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
		if(_countMyTurn % Flytrapper_ANI_COUNT == 0)
		{
			_currentFrameX++;
			if(_state3 == ATTACK3)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if(_currentFrameX == 4)
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
							_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
							_currentFrameX = 0;
							_state3 = IDLE3;

							_isDelay = false;
						}
					}
				}
			}

			if(_state3 == SKILL3)
			{
				//에너미 몇 프레임에서 공격을 할 지 정한다
				if(_currentFrameX == 6 || _currentFrameX == 7 || _currentFrameX == 8)
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
							_enemyImg = IMAGEMANAGER->findImage("flytrapper_idle");
							_currentFrameX = 0;
							_state3 = IDLE3;

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

void bsFlytrapper::render(void)
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


void bsFlytrapper::myTurnAttack(int playerIndex)
{
	int rndSkill = RND->getInt(3);
	_turnState = MYTURN;
	if(rndSkill == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("flytrapper_skill");
		_state3 = SKILL3;
	}
	else
	{
		_enemyImg = IMAGEMANAGER->findImage("flytrapper_attack");
		_state3 = ATTACK3;
	}
	_currentFrameX = 0;
	//어택시 에너미 위치 잡아주는 코드
	_destX = WINSIZEX * 0.5f;
	if (playerIndex == 0)
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

void bsFlytrapper::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("flytrapper_getdmg");
	_currentFrameX = 0;
	_state3 = GETDMG3;
	_hp -= playerAtt * playerAtt / _def + 1;
	EFFECTMANAGER->addEffect(RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65), RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight()), "bsEffect_attack");
}