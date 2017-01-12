#include "stdafx.h"
#include "bsEnemy.h"

void bsEnemy::setPrevPos(float x, float y)
{
	_prevX = x;
	_prevY = y;
}

POINT bsEnemy::getPrevPos()
{
	POINT prevPos;
	prevPos.x = _prevX;
	prevPos.y = _prevY;

	return prevPos;
}

void bsEnemy::setDestPos(float x, float y)
{
	_destX = x;
	_destY = y;
}