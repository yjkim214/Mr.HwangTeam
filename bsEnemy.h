#pragma once
#include "gameNode.h"
class bsEnemy : public gameNode
{
protected:
	int		_att;
	int		_def;

	int		_hp;
	int		_maxHp;
	int		_mp;
	int		_maxMp;

protected:
	float	_prevX, _prevY;
	float	_destX, _destY;

protected:
	bool	_isDead;

protected:
	image*	_enemyImg;
	int		_currentFrameX;
	int		_countNotMyTurn;
	int		_countMyTurn;
	int		_countTurnEnd;

protected:
	bool	_isDelay;
	int		_delayCount;

protected:
	TURN_STATE _turnState;

public:
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	virtual void myTurn() = 0;
	virtual void getDmg(int playerAtt) = 0;

	//=============================================================
	//	## enemy ## (접근자 / 설정자)
	//=============================================================
public:
	int getAtt() { return _att; }
	int getDef() { return _def; }
	int getHp() { return _hp; }
	int getMp() { return _mp; }

public:
	void setPrevPos(float x, float y);
	POINT getPrevPos();
	void setDestPos(float x, float y);

public:
	bool getIsDead() { return _isDead; }

public:
	TURN_STATE getTurnState() { return _turnState; }

	bsEnemy() {}
	~bsEnemy() {}
};