#pragma once
#include "bsEnemy.h"

enum DEVILBOMBER_STATE
{
	IDLE5,
	ATTACK5,
	SKILL5,
	GETDMG5,
	DEAD5,
};

class bsDevilBomber : public bsEnemy
{
private:
	DEVILBOMBER_STATE _state5;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int playerIndex);
	virtual void getDmg(int playerAtt);

	bsDevilBomber() {}
	~bsDevilBomber() {}
};