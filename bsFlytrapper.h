#pragma once
#include "bsEnemy.h"

enum class FLYTRAPPER_STATE
{
	IDLE,
	ATTACK,
	SKILL,
	GETDMG,
	DEAD,
};

class bsFlytrapper : public bsEnemy
{
private:
	FLYTRAPPER_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn(int playerIndex);
	virtual void getDmg(float playerAtt);

	bsFlytrapper() {}
	~bsFlytrapper() {}
};