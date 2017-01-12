#include "stdafx.h"
#include "AlexNoah.h"

#define ALEXNOAH_ATT		5
#define ALEXNOAH_DEF		5
#define ALEXNOAH_MAXHP		100
#define ALEXNOAH_MAXMP		20
#define ALEXNOAH_ANI_COUNT	10

HRESULT AlexNoah::init(void)
{
	_att = ALEXNOAH_ATT;
	_def = ALEXNOAH_DEF;

	_hp = ALEXNOAH_MAXHP;
	_maxHp = ALEXNOAH_MAXHP;
	_mp = ALEXNOAH_MAXMP;
	_maxMp = ALEXNOAH_MAXMP;

	_prevX = 0;
	_prevY = 0;
	_destX = 0;
	_destY = 0;

	_rc = RectMake(_prevX, _prevY, 80, 160);

	_playerImg;
	_count = 0;

	_isDead = false;

	_turnState = NOTMYTURN;

	return S_OK;
}

void AlexNoah::release(void)
{
}

void AlexNoah::update(void)
{
	if (_turnState == NOTMYTURN)
	{
		_rc = RectMake(_prevX, _prevY, 80, 100);
	}

	else if (_turnState == MYTURN)
	{

	}

	else if (_turnState == TURNEND)
	{
		_turnState = NOTMYTURN;
	}
}

void AlexNoah::render(void)
{
	if (!_isDead)
	{
		RectangleMake(getMemDC(), _rc);
	}
}

void AlexNoah::myTurn()
{
	_turnState = MYTURN;
}

void AlexNoah::getDmg(int enemyAtt)
{
}