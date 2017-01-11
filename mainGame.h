#pragma once
#include "gameNode.h"
/*�����δ� �� ������ϸ� �߰����ش�*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

