#pragma once
#include "bsEnemy.h"

enum class DEVILBOMBER_STATE
{
	IDLE,
	ATTACK,
	SKILL,
	GETDMG,
	DEAD,
};

class bsDevilBomber : public bsEnemy
{
private:
	DEVILBOMBER_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn(int playerIndex);
	virtual void getDmg(float playerAtt);

	bsDevilBomber() {}
	~bsDevilBomber() {}
};