#include "stdafx.h"
#include "bsDevilBomber.h"

#define DevilBomber_ATT		6
#define DevilBomber_DEF		6
#define DevilBomber_MAXHP		50
#define DevilBomber_MAXMP		10
#define DevilBomber_ANI_COUNT	10

HRESULT bsDevilBomber::init(void)
{
	_att = DevilBomber_ATT;
	_def = DevilBomber_DEF;

	_hp = DevilBomber_MAXHP;
	_maxHp = DevilBomber_MAXHP;
	_mp = DevilBomber_MAXMP;
	_maxMp = DevilBomber_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_isSelected = true;
	_isAttack = false;
	_isDead = false;

	_enemyImg = IMAGEMANAGER->findImage("devilBomber_idle");
	_currentFrameX = 0;

	_countNotMyTurn = 0;
	_countMyTurn = 0;
	_countTurnEnd = 0;

	_isDelay = true;
	_delayCount = 0;

	_turnState = NOTMYTURN;

	_state5 = IDLE5;

	return S_OK;
}

void bsDevilBomber::release(void)
{
}

void bsDevilBomber::update(void)
{
	if(_turnState == NOTMYTURN)
	{
		_countNotMyTurn++;
		if(_countNotMyTurn % DevilBomber_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state5 == IDLE5)
			{
				//�ִϸ��̼� ������ �ݺ�
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
			}

			if(_state5 == GETDMG5)
			{
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= 5)
						{
							_turnState = TURNEND;

							//�������� �޾��� ��
							if(_hp <= 0)
							{
								_enemyImg = IMAGEMANAGER->findImage("devilBomber_dead");
								_currentFrameX = 0;
								//hp�� �ٴ��̸� ���� ���·� �ٲ�
								_state5 = DEAD5;
							}
							else
							{
								_enemyImg = IMAGEMANAGER->findImage("devilBomber_idle");
								_currentFrameX = 0;
								_state5 = IDLE5;
							}
							_isDelay = false;
						}
					}
				}
			}

			if(_state5 == DEAD5)
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
		if(_countMyTurn % DevilBomber_ANI_COUNT == 0)
		{
			_currentFrameX++;

			if(_state5 == ATTACK5)
			{
				//���ʹ� �� �����ӿ��� ������ �� �� ���Ѵ�
				if(_currentFrameX == 3)
				{
					_isAttack = true;
				}
				//�ٽ� ��� ���·� ����
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= 5)
						{
							_turnState = TURNEND;
							_enemyImg = IMAGEMANAGER->findImage("devilBomber_idle");
							_currentFrameX = 0;
							_state5 = IDLE5;

							_isDelay = false;
						}
					}
				}
			}

			if(_state5 == SKILL5)
			{
				//���ʹ� �� �����ӿ��� ������ �� �� ���Ѵ�
				if(_currentFrameX == 8 || _currentFrameX == 9 || _currentFrameX == 10)
				{
					_isAttack = true;
				}
				//�ٽ� ��� ���·� ����
				if(_currentFrameX > _enemyImg->getMaxFrameX())
				{
					if(_isDelay)
					{
						_delayCount++;
						if(_delayCount >= 5)
						{
							_turnState = TURNEND;
							_enemyImg = IMAGEMANAGER->findImage("devilBomber_idle");
							_currentFrameX = 0;
							_state5 = IDLE5;

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

void bsDevilBomber::render(void)
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

void bsDevilBomber::myTurnAttack(int playerIndex)
{
	int rndSkill = RND->getInt(3);
	_turnState = MYTURN;
	if(rndSkill == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("devilBomber_skill");
		_state5 = SKILL5;
	}
	else
	{
		_enemyImg = IMAGEMANAGER->findImage("devilBomber_attack");
		_state5 = ATTACK5;
	}

	_currentFrameX = 0;

	//���ý� ���ʹ� ��ġ ����ִ� �ڵ�
	_destX = WINSIZEX * 0.6f;
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

void bsDevilBomber::getDmg(int playerAtt)
{
	_enemyImg = IMAGEMANAGER->findImage("devilBomber_getdmg");
	_currentFrameX = 0;
	_state5 = GETDMG5;
	_hp -= playerAtt * playerAtt / _def + 1;
	EFFECTMANAGER->addEffect(RND->getFromIntTo(_prevX + 30, _prevX + _enemyImg->getFrameWidth() - 65), RND->getFromIntTo(_prevY + 75, _prevY + _enemyImg->getFrameHeight()), "bsEffect_attack");
}