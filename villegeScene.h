#pragma once
#include "gameNode.h"
class villegeScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	villegeScene() {}
	~villegeScene() {}
};

