#pragma once
#include "bsPlayer.h"

enum ALEXNOAH_STATE
{
	IDLE,
	ATTACK,
	GETDMG,
	DEAD,
};

class AlexNoah : public bsPlayer
{
private:
	ALEXNOAH_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurn();
	virtual void getDmg(int enemyAtt);

	AlexNoah() {}
	~AlexNoah() {}
};