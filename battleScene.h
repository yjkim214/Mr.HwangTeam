#pragma once
#include "gameNode.h"

class bsPlayerManager;
class bsEnemyManager;

enum BS_STATE
{
	PLAYERTURN,
	ENEMYTURN,
};

class battleScene : public gameNode
{
private:
	bsPlayerManager* _pm;
	bsEnemyManager* _em;

private:
	BS_STATE _bsState;

private:
	int _currentPlayerIndex;
	int _currentEnemyIndex;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene() {}
	~battleScene() {}
};