#pragma once
#include "gameNode.h"
#include "villageMap.h"
#include "Owplayer.h"
class mainMenuScene : public gameNode
{
private:
	RECT rc[3];
	bool isNewGame;
	bool isLoad;
	bool isExit;

	bool _isLoading;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getIsLoading() { return _isLoading; }

	mainMenuScene() {}
	~mainMenuScene() {}
};

