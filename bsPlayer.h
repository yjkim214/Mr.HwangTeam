#pragma once
#include "gameNode.h"
#include "bullet.h"

class bsPlayer : public gameNode
{
protected:
	float	_att;
	float	_def;

	float	_hp;
	float	_maxHp;
	float	_mp;
	float	_maxMp;

protected:
	float	_prevX, _prevY;
	float	_destX, _destY;

protected:
	image*	_playerImg;
	int		_currentFrameX;

protected:
	int		_countNotMyTurn;
	int		_countMyTurn;
	int		_countTurnEnd;

protected:
	bool	_isDelay;
	int		_delayCount;

protected:
	bool	_isAttack;
	bool	_isHeal;
	bool	_isDead;

protected:
	TURN_STATE _turnState;

protected:
	bullet*	_bullet;
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

	virtual bullet* getBullet() { return NULL; }
	//=============================================================
	//	## player ## (접근자 / 설정자)
	//=============================================================
	int getAtt() { return _att; }
	int getDef() { return _def; }
	int getHp() { return _hp; }
	int getMp() { return _mp; }

	void setPrevPos(float x, float y);
	POINT getPrevPos();

	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsHeal() { return _isHeal; }
	void setIsHeal(bool isHeal) { _isHeal = isHeal; }
	bool getIsDead() { return _isDead; }

	TURN_STATE getTurnState() { return _turnState; }

public:
	bsPlayer() {}
	~bsPlayer() {}
};