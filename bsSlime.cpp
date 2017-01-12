#include "stdafx.h"
#include "bsSlime.h"

#define SLIME_ATT		2
#define SLIME_DEF		2
#define SLIME_MAXHP		50
#define SLIME_MAXMP		10
#define SLIME_ANI_COUNT	10

HRESULT bsSlime::init(void)
{
	_att = SLIME_ATT;
	_def = SLIME_DEF;

	_hp = SLIME_MAXHP;
	_maxHp = SLIME_MAXHP;
	_mp = SLIME_MAXMP;
	_maxMp = SLIME_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("slime_idle");
	_count = 0;

	_turnState = NOTMYTURN;

	_state = IDLE;

	return S_OK;
}

void bsSlime::release(void)
{
}

void bsSlime::update(void)
{
	_count++;

	if (_turnState == NOTMYTURN)
	{
		if (_count % SLIME_ANI_COUNT == 0)
		{
			_enemyImg->setFrameX(_enemyImg->getFrameX() + 1);

			if (_state == IDLE)
			{
				//애니메이션 무한정 반복
				if (_enemyImg->getFrameX() >= _enemyImg->getMaxFrameX())
				{
					_enemyImg->setFrameX(0);
				}
			}

			if (_state == GETDMG)
			{
				if (_enemyImg->getFrameX() >= _enemyImg->getMaxFrameX())
				{
					//데미지를 받았을 시
					if (_hp <= 0)
					{
						//hp가 바닥이면 죽은 상태로 바꿈
						_state = DEAD;
					}

					else
					{
						//아니면 다시 대기 상태로 돌입
						_enemyImg = IMAGEMANAGER->findImage("slime_idle");
						_enemyImg->setFrameX(0);
						_state = IDLE;
					}
				}
			}

			if (_state == DEAD)
			{
				if (_enemyImg->getFrameX() >= _enemyImg->getMaxFrameX())
				{
					_isDead = true;
				}
			}

			_count = 0;
		}
	}

	else if (_turnState == MYTURN)
	{
		if (_count % SLIME_ANI_COUNT == 0)
		{
			_enemyImg->setFrameX(_enemyImg->getFrameX() + 1);

			if (_state == ATTACK)
			{
				//다시 대기 상태로 돌입
				if (_enemyImg->getFrameX() >= _enemyImg->getMaxFrameX())
				{
					_turnState = TURNEND;
					_enemyImg = IMAGEMANAGER->findImage("slime_idle");
					_enemyImg->setFrameX(0);
					_state = IDLE;
				}
			}

			_count = 0;
		}
	}

	else if (_turnState == TURNEND)
	{
		_turnState = NOTMYTURN;
	}
}

void bsSlime::render(void)
{
	if (!_isDead)
	{
		if (_turnState == MYTURN)
		{
			_enemyImg->frameRender(getMemDC(), _destX, _destY);
		}

		else if (_turnState == NOTMYTURN)
		{
			_enemyImg->frameRender(getMemDC(), _prevX, _prevY);
		}
	}
}

void bsSlime::myTurn()
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("slime_attack");
	_enemyImg->setFrameX(0);
	_state = ATTACK;
}

void bsSlime::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("slime_getdmg");
	_enemyImg->setFrameX(0);
	_state = GETDMG;
}