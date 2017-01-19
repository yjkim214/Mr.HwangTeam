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