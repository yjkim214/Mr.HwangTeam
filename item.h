#pragma once
#include "gameNode.h"
class item :public gameNode
{

private:
	//아이템 이미지 및 그려줄 위치
	image* _imgItem;
	float _x, _y;
private:
	int _att;
	int _def;
	int _matt;
	int _cost;
	int _hp;
	int _mp;
	char* _imagkey;
	RECT _itemRect;

	ITEM_KIND _kind;


public:
	//이미지를 키값으로 받아줌 아이템의 공격력, 방어력, 마력등을 초기에 설정
	HRESULT init(char* imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	void initpotion(char*imgKey, int hp, int mp, ITEM_KIND kind, int cost);
	void release(void);
	void update(void);
	void render(void);

	int getAtt() { return _att; }
	void setAtt(int att) { _att = att; }
	int getDef() { return _def; }
	void setDef(int def) { _def = def; }
	int getMatt() { return _matt; }
	void setMatt(int matt) { _matt = matt; }
	int getcost() { return _cost; }
	char* getkey() { return _imagkey; }
	void setkey(char* key) { _imagkey = key; }
	int getHp() { return _hp; }
	void setHp(int set) { _hp = set; }
	int getMp() { return _mp; }
	void setMp(int set) { _mp = set; }

	//위치를 항상 고정 시켜줌
	void setPos(float x, float y);
	void setRect(RECT rect) { _itemRect = rect; }
	void setCost(int cost) { _cost = cost; }

	RECT getRect() { return _itemRect; }

	ITEM_KIND getkind() { return _kind; }

	image* getImage() { return _imgItem; }

	item() {}
	~item() {}
};

