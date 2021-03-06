#pragma once
#include "gameNode.h"

class bsPlayerManager;
class bsEnemyManager;

enum BS_STATE
{
	START, 
	PLAYERTURN, 
	ENEMYTURN,
};

enum USER_SELECT
{
	ATTACK,
	SKILL,
	DEFENSE,
	GETAWAY,
	SELECT,
	INIT,
};

enum class ENEMYTURNSTATE
{
	START,
	UPDATE,
};

enum class PLAYERTURNSTATE
{
	START,
	UPDATE,
};

class battleScene : public gameNode
{
private:
	bsPlayerManager*	_pm;
	bsEnemyManager*		_em;

private:
	BS_STATE			_bsState;
	USER_SELECT			_userSelect;
	ENEMYTURNSTATE		_enemyTurnState;
	PLAYERTURNSTATE		_playerTurnState;

private:
	int		_currentPlayerIndex;
	int		_currentEnemyIndex;

private:
	int		_actionSelected;
	int		_enemySelected;
	int		_playerSelected;

private:
	image*	_uiAttack;
	image*	_uiSkill;
	image*	_uiDefense;
	image*	_uiGetaway;

private:
	image*	_background;

private:
	image*	_fadeImg;
	int		_alpha;

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