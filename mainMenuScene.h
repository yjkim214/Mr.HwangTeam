#pragma once
#include "gameNode.h"
class mainMenuScene : public gameNode
{
private:
	RECT rc[3];
	bool isNewGame;
	bool isLoad;
	bool isExit;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	mainMenuScene() {}
	~mainMenuScene() {}
};

