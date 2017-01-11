#pragma once
#include "gameNode.h"
#include "villageMap.h"
class villageScene : public gameNode
{
private:
	villageMap* _villageMap;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	villageScene() {}
	~villageScene() {}
};

