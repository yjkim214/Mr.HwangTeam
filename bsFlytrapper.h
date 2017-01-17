#pragma once
#include "bsEnemy.h"

enum FLYTRAPPER_STATE
{
	IDLE3,
	ATTACK3,
	SKILL3,
	GETDMG3,
	DEAD3,
};

class bsFlytrapper : public bsEnemy
{
private:
	FLYTRAPPER_STATE _state3;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int playerIndex);
	virtual void getDmg(int playerAtt);

	bsFlytrapper() {}
	~bsFlytrapper() {}
};