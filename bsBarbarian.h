#pragma once
#include "bsEnemy.h"

enum class BARBARIAN_STATE
{
	IDLE,
	ATTACK,
	GETDMG,
	DEAD,
};

class bsBarbarian : public bsEnemy
{
private:
	BARBARIAN_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn(int playerIndex);
	virtual void getDmg(float playerAtt);

	bsBarbarian() {}
	~bsBarbarian() {}
};