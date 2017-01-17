#pragma once
#include "bsPlayer.h"

enum class LUNAR_STATE
{
	IDLE,
	ATTACK,
	SKILL,
	GETDMG,
	DEAD,
};

class Lunar : public bsPlayer
{
private:
	LUNAR_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void myTurnAttack(int enemyIndex);
	virtual void myTurnSkill(int enemyIndex);
	virtual void getDmg(int enemyAtt);

	Lunar() {}
	~Lunar() {}
};