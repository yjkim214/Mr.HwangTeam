#pragma once
#include "gameNode.h"
class bsPlayer : public gameNode
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
	RECT	_rc;

protected:
	image*	_playerImg;
	int		_count;

protected:
	bool	_isDead;

protected:
	TURN_STATE _turnState;

public:
	//=============================================================
	//	## player ## (순수 가상 함수)
	//=============================================================
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	virtual void myTurn() = 0;
	virtual void getDmg(int enemyAtt) = 0;

	//=============================================================
	//	## player ## (접근자 / 설정자)
	//=============================================================
	int getAtt() { return _att; }
	int getDef() { return _def; }
	int getHp() { return _hp; }
	int getMp() { return _mp; }

	void setPrevPos(float x, float y);
	POINT getPrevPos();

	bool getIsDead() { return _isDead; }

public:
	bsPlayer() {}
	~bsPlayer() {}
};