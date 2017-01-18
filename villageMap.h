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
	int _state;
	image* _pixelVillage;
	image* _pixelHouse1;
	image* _pixelHouse2;
	image* _pixelStroe;
	image* _pixelShop;
	image* _pixelHotel1;
	image* _pixelHotel2;
	image* _pixelHouse3;
	image* _pixelHouse4;
	image* _pixelDungeon;
	image* _pixelBoss;


	RECT _playeRc;
	RECT _selectRc[2];
	int _loofX;
	int _bgX;
	int _bgY;

	bool is1Floor;
	bool isDungeon;
	bool isBoss;

	bool _isMenu;
	bool _isSaveSelect;
	bool _isMenuSelect;


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
	//void dungeonPixelCol();
	void bossRoomPixelCol();

	void menuSelect();
	void menuRender();

	void setOWPlayer(Owplayer* owPlayer) { _owPlayer = owPlayer; }

	int getBgX() { return _bgX; }
	void setBgX(int bgX)
	{
		_bgX = bgX;

		if (_bgX < 0)
		{
			_bgX = 0;
		}
	}
	int getBgY() { return _bgY; }
	void setBgY(int bgY)
	{
		_bgY = bgY;
		if (_bgY < 0)
		{
			_bgY = 0;
		}
	}
	int getState() { return _state; }
	void setState(int state) { _state = state; }
	image* getPixelVillage() { return _pixelVillage; }
	bool getIsMenu() { return _isMenu; }
	image* getPixelBoss() { return _pixelBoss; }
	villageMap() {}
	~villageMap() {}
};

