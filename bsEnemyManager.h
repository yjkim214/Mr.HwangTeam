#pragma once
#include "gameNode.h"

class bsEnemy;
class bsSlime;

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

	vector<bsEnemy*> getVEnemyList() { return _vEnemyList; }
	void selectedEnemy(int select);
	void endSelect();
public:
	bsEnemyManager() {}
	~bsEnemyManager() {}
};

