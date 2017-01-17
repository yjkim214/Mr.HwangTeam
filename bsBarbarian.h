#pragma once
#include "bsEnemy.h"

enum BARBARIAN_STATE
{
	IDLE4,
	ATTACK4,
	GETDMG4,
	DEAD4,
};

class bsBarbarian : public bsEnemy
{
private:
	BARBARIAN_STATE _state4;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int playerIndex);
	virtual void getDmg(int playerAtt);

	bsBarbarian() {}
	~bsBarbarian() {}
};