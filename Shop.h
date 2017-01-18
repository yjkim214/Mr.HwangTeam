#pragma once
#include "gameNode.h"


class item;
class Owplayer;

class Shop : public gameNode
{
public:
	Owplayer* _Owplayer;
	vector<item*> _shoplist;
	vector<item*> _shoppotionlist;
	bool _isopen;
	image* _shop;
	RECT _Exit;
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addItem(char * imgKey, int att, int def, int matt, ITEM_KIND kind, float x, float y, int cost);
	void addPotion(char* imgKey, int hp, int mp, ITEM_KIND kind, int cost, float x, float y);
	void setOwPlayer(Owplayer* player);

	bool getIsOpen() { return _isopen; }
	void closeShop() { _isopen = false; }
	void openShop() { _isopen = true; }

	Shop() {}
	~Shop() {}
};