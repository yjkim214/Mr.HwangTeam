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
	image*	_playerImg;
	int		_currentFrameX;

protected:
	bool	_isDelay;
	int		_delayCount;

protected:
	int		_countNotMyTurn;
	int		_countMyTurn;
	int		_countTurnEnd;

protected:
	bool	_isAttack;
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

	virtual void myTurnAttack(int enemyIndex) = 0;
	virtual void myTurnSkill(int enemyIndex) = 0;
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

	bool getIsAttack() { return _turnState; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsDead() { return _isDead; }

	TURN_STATE getTurnState() { return _turnState; }

public:
	bsPlayer() {}
	~bsPlayer() {}
};