#pragma once
#include "bsEnemy.h"

enum class FLUFFYBUG_STATE
{
	IDLE,
	ATTACK,
	GETDMG,
	DEAD,
};

class bsFluffyBug : public bsEnemy
{
private:
	FLUFFYBUG_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn(int playerIndex);
	virtual void getDmg(float playerAtt);

	bsFluffyBug() {}
	~bsFluffyBug() {}
};