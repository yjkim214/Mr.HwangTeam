#pragma once
#include "bsEnemy.h"

enum SLIME_STATE
{
	IDLE,
	ATTACK,
	GETDMG,
	DEAD,
};

class bsSlime : public bsEnemy
{
private:
	SLIME_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn();
	virtual void getDmg(int playerAtt);

	bsSlime() {}
	~bsSlime() {}
};