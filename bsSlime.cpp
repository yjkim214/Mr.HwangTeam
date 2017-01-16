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

	_isSelected = true;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("slime_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state = IDLE;

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
		if (_countNotMyTurn % SLIME_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if (_state == IDLE)
			{
				//�ִϸ��̼� ������ �ݺ�
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if (_state == GETDMG)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					//�������� �޾��� ��
					if (_hp <= 0)
					{
						//hp�� �ٴ��̸� ���� ���·� �ٲ�
						_state = DEAD;
					}

					else
					{
						if (!_isDelay)
						{
							_delayCount++;
							if (_delayCount >= 5)
							{
								_turnState = TURNEND;
								//�ƴϸ� �ٽ� ��� ���·� ����
								_enemyImg = IMAGEMANAGER->findImage("slime_idle");
								_currentFrameX = 0;
								_state = IDLE;

								_isDelay = true;
							}
						}
					}
				}
			}

			if (_state == DEAD)
			{
				if (_currentFrameX > _enemyImg->getMaxFrameX())
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
		if (_countMyTurn % SLIME_ANI_COUNT == 0)
		{
			_currentFrameX++;
			if (_state == ATTACK)
			{
				//���ʹ� �� �����ӿ��� ������ �� �� ���Ѵ�
				if (_currentFrameX == 3)
				{
					_isAttack = true;
				}
				//�ٽ� ��� ���·� ����
				if (_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if (_isDelay)
					{
						_delayCount++;
						if (_delayCount >= 5)
						{
							_turnState = TURNEND;
							_enemyImg = IMAGEMANAGER->findImage("slime_idle");
							_currentFrameX = 0;
							_state = IDLE;

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

void bsSlime::myTurnAttack(int playerIndex)
{
	_turnState = MYTURN;
	_enemyImg = IMAGEMANAGER->findImage("slime_attack");
	_currentFrameX = 0;
	_state = ATTACK;
	//���ý� ���ʹ� ��ġ ����ִ� �ڵ�
	_destX = WINSIZEX * 0.5f;
	if (playerIndex == 0)
	{
		_destY = 0;
	}

	else if (playerIndex == 1)
	{
		_destY = WINSIZEY * 0.25f;
	}

	else
	{
		_destY = WINSIZEY * 0.5f;
	}
}

void bsSlime::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("slime_getdmg");
	_currentFrameX = 0;
	_state = GETDMG;
}