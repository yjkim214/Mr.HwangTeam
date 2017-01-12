#pragma once
#include "gameNode.h"
#include "villageMap.h"
#include "Owplayer.h"
class villageScene : public gameNode
{
private:
	villageMap* _villageMap;
	Owplayer* _Owplayer;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	villageScene() {}
	~villageScene() {}
};

