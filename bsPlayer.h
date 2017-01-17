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

protected:
	bool	_isDelay;
	int		_delayCount;

protected:
	bool	_isAttack;
	bool	_isHeal;
	bool	_isDefense;
	bool	_isVictory;
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
	virtual void myTurnDefense() = 0;
	virtual void victoryBattle() = 0;
	virtual void getDmg(int enemyAtt) = 0;

public:
	virtual bullet* getBullet() { return NULL; }
	//=============================================================
	//	## player ## (접근자 / 설정자)
	//=============================================================
	float getAtt() { return _att; }
	float getDef() { return _def; }
	float getHp() { return _hp; }
	float getMp() { return _mp; }

public:
	void setPrevPos(float x, float y);
	POINT getPrevPos();

public:
	bool getIsAttack() { return _isAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsHeal() { return _isHeal; }
	void setIsHeal(bool isHeal) { _isHeal = isHeal; }
	void setIsDefense(bool isDefense) { _isDefense = isDefense; }
	bool getIsVictory() { return _isVictory; }
	bool getIsDead() { return _isDead; }

public:
	TURN_STATE getTurnState() { return _turnState; }

public:
	bsPlayer() : _prevX(0), _prevY(0), _destX(0), _destY(0),
		_currentFrameX(0),
		_countNotMyTurn(0), _countMyTurn(0), 
		_isDelay(true), _delayCount(0), 
		_isAttack(false), _isHeal(false), _isDefense(false), _isVictory(false), _isDead(false), 
		_turnState(NOTMYTURN), 
		_bullet(NULL)
	{

	}

	~bsPlayer() {}
};