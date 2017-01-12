#pragma once
#include "gameNode.h"

enum E_MAPSTATE
{
	VILLAGE,
	HOUSE1,
	HOUSE2,
	STORE,
	SHOP,
	HOTEL1,
	HOTEL2,
	HOUSE3,
	HOUSE4,
	DUNGEON,
	BOSSROOM,

};

class Owplayer;

class villageMap : public gameNode
{
private:
	RECT _playeRc;
	int _loofX;
	int _bgX;
	int _bgY;
	E_MAPSTATE _state;

	Owplayer* _owPlayer;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void check();
	void setOWPlayer(Owplayer* owPlayer) { _owPlayer = owPlayer; }

	int getBgX() { return _bgX; }
	void setBgX(int bgX) { _bgX = bgX; }
	int getBgY() { return _bgY; }
	void setBgY(int bgY) { _bgY = bgY; }
	E_MAPSTATE getState() { return _state; }

	villageMap() {}
	~villageMap() {}
};


