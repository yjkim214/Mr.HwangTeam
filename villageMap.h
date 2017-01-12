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
	E_MAPSTATE _state;
	image* _pixelVillage;
	image* _pixelHouse1;
	RECT _playeRc;
	int _loofX;
	int _bgX;
	int _bgY;


	Owplayer* _owPlayer;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void check();

	//픽셀 충돌함수
	void villagePixelCol();
	void house1PixelCol();
	void house2PixelCol();
	void storePixelCol();
	void shopPixelCol();
	void hotel1PixelCol();
	void hotel2PixelCol();
	void house3PixelCol();
	void house4PixelCol();
	void dungeonPixelCol();
	void bossRoomPixelCol();

	void setOWPlayer(Owplayer* owPlayer) { _owPlayer = owPlayer; }



	int getBgX() { return _bgX; }
	void setBgX(int bgX) { _bgX = bgX; }
	int getBgY() { return _bgY; }
	void setBgY(int bgY) { _bgY = bgY; }
	E_MAPSTATE getState() { return _state; }

	villageMap() {}
	~villageMap() {}
};

