#pragma once
#include "gameNode.h"

class bsEnemy;
class bsSlime;
class bsFluffyBug;
class bsFlytrapper;
class bsBarbarian;
class bsDevilBomber;

class bsEnemyManager : public gameNode
{
private:
	vector<bsEnemy*> _vEnemyList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addSlime(float prevX, float prevY);
	void addFluffyBug(float prevX, float prevY);
	void addFlytrapper(float prevX, float prevY);
	void addBarbarian(float prevX, float prevY);
	void addDevilBomber(float prevX, float prevY);

	vector<bsEnemy*> getVEnemyList() { return _vEnemyList; }
	void selectedEnemy(int select);
	void endSelect();
public:
	bsEnemyManager() {}
	~bsEnemyManager() {}
};

