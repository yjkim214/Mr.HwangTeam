#pragma once
#include "gameNode.h"
#include "villageMap.h"
#include "Owplayer.h"
struct tagNPC
{
	float x, y;
	float ealryX;
	float ealryY;
	float endX;
	float endY;
	bool isLeft;
	bool isDown;
	RECT rc;
};
class villageScene : public gameNode
{
private:
	villageMap* _villageMap;
	Owplayer* _Owplayer;
	tagNPC _npc[5];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void camera();
	void npcinit();
	void npcUpdate();
	void npcRender();

	villageScene() {}
	~villageScene() {}
};

