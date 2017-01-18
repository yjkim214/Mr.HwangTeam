#pragma once
#include "bsEnemy.h"

enum class BOSS_STATE
{
	IDLE,
	ATTACK,
	SKILL01,
	SKILL02,
	GETDMG,
	DEAD,
};

class bsBoss : public bsEnemy
{
private:
	BOSS_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int playerIndex);
	virtual void getDmg(int playerAtt);

	bsBoss() {}
	~bsBoss() {}
};