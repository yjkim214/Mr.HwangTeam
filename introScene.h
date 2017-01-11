#pragma once
#include "gameNode.h"
class introScene : public gameNode
{
private:
	image* _startImage;
	int frameX;
	int time;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	introScene() {}
	~introScene() {}
};

