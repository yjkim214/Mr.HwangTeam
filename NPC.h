#pragma once
#include "gameNode.h"
#include "chat.h"

class villageMap;
class Owplayer;

enum E_NPCSTATE
{
	MOVE,
	STOP,
};

struct tagNPC
{
	float x, y;
	float ealryX;
	float ealryY;
	float endX;
	float endY;
	float plusX;
	float plusY;
	bool isLeft;
	bool isDown;
	bool isChat;
	int frameX;
	int frameY;
	RECT crashRc;
	RECT rc;
	E_NPCSTATE State;
};

class NPC : public gameNode
{
private:
	villageMap* _villageMap;
	Owplayer* _owPlayer;
	chat* _chat;
	tagNPC _npc[5];
	int frameCount;
	int _chatCount;
	bool _chatEnd;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void check();

	void setRefer(villageMap* villageMap, Owplayer* owPlayer);
	void camera();
	void npcInit();
	void npcUpdate();
	void npcRender();
	void col();
	void NPCchat();
	void chatRender();

	tagNPC getNpc(int index) { return _npc[index]; }
	void setX(float x, int index) { _npc[index].x = x; }
	void setY(float y, int index) { _npc[index].y = y; }
	void setState(E_NPCSTATE state) { _npc[4].State = state; }

	NPC() {}
	~NPC() {}
};

