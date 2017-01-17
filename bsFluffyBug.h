#pragma once
#include "bsEnemy.h"

enum FLUFFYBUG_STATE
{
	IDLE2,
	ATTACK2,
	GETDMG2,
	DEAD2,
};

class bsFluffyBug : public bsEnemy
{
private:
	FLUFFYBUG_STATE _state2;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int playerIndex);
	virtual void getDmg(int playerAtt);

	bsFluffyBug() {}
	~bsFluffyBug() {}
};