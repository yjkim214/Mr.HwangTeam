#pragma once
#include "gameNode.h"
/*�����δ� �� ������ϸ� �߰����ش�*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "mainMenuScene.h"
#include "introScene.h"
#include "villageScene.h"
#include "battleScene.h"
#include "owDungeon.h"
#include "ending.h"

class mainGame : public gameNode
{
private:
	mainMenuScene* _mainMenu;
	villageScene* _villageScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

