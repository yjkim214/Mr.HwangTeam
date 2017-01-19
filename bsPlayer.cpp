#include "stdafx.h"
#include "bsPlayer.h"

void bsPlayer::setPrevPos(float x, float y)
{
	_prevX = x;
	_prevY = y;
}

POINT bsPlayer::getPrevPos()
{
	POINT prevPos;
	prevPos.x = _prevX;
	prevPos.y = _prevY;

	return prevPos;
}

void bsPlayer::setXp(float xp)
{
	if (_lv < 5)
	{
		if (xp >= _maxXp)
		{
			xp -= _maxXp;
			_xp = 0;
			_maxXp += 100;
			levelUp();
		}
	}

	_xp += xp;
}

void bsPlayer::levelUp()
{
	_att += 10;
	_def += 10;
	_maxHp *= 2;
	_hp = _maxHp;
	_maxMp += 100;
	_mp = _maxMp;
	_lv++;
}