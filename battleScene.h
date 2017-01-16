#pragma once
#include "gameNode.h"

class bsPlayerManager;
class bsEnemyManager;

enum BS_STATE
{
	PLAYERTURN,
	ENEMYTURN,
};

enum USER_SELECT
{
	ATTACK, 
	SKILL, 
	DEFENSE, 
	GETAWAY, 
	SELECTED, 
	INIT, 
};

class battleScene : public gameNode
{
private:
	bsPlayerManager* _pm;
	bsEnemyManager* _em;

private:
	BS_STATE _bsState;
	USER_SELECT _userSelect;

private:
	int _currentPlayerIndex;
	int _currentEnemyIndex;

private:
	int _actionSelected;
	int _enemySelected;

private:
	image* _uiAttack;
	image* _uiSkill;
	image* _uiDefense;
	image* _uiGetaway;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setPlayerIndex();
	void selectAction();
	void selectEnemy();
	void setEnemyIndex();
	void setUiImage();

	battleScene() {}
	~battleScene() {}
};