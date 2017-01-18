#pragma once
#include "gameNode.h"
class item;
class Owplayer;

enum state
{
	WEAPON,
	EQUIP,
	POTION,
	QUEST
};

class inventory : public gameNode
{
public:
	image*_inven;
	bool _isopen;
	RECT _invenRect;
	state _state;

	bool _isShopOpen;

	Owplayer* _Owplayer;
private:
	float _ptPrevX, _ptPrevY;

public:
	// Inventory - Rect.

	RECT _Exit;
	RECT _Weapon;
	RECT _Equip;
	RECT _Potion;
	RECT _Quest;
	vector<item*> _vinvenlist;
	vector<item*> _vEquiplist;
	vector<item*> _vpotionlist;

public:
	item* _item;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	void addInven(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	void addEquip(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	void addpotion(char* imgKey, int hp, int mp, ITEM_KIND kind, int cost);
	void setOwPlayer(Owplayer* player);

public:
	bool getIsOpen() { return _isopen; }
	void closeInventory() { _isopen = false; }
	void openInventory() { _isopen = true; }

	void isShopOpen(bool shopOpen) { _isShopOpen = shopOpen; }
	image* getinvenimg() { return _inven; }
	inventory() {}
	~inventory() {}
};