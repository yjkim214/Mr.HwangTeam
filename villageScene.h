#pragma once
#include "gameNode.h"
#include "mainMenuScene.h"
#include "villageMap.h"
#include "Owplayer.h"
#include "NPC.h"
#include "Shop.h"

class villageScene : public gameNode
{
private:
	villageMap* _villageMap;
	Owplayer* _Owplayer;
	NPC* _npc;
	mainMenuScene* _mainMenu;
	Shop* _Shop;

	int time;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMain(mainMenuScene* main) { _mainMenu = main; }

	void Load();

	villageScene() {}
	~villageScene() {}
};

