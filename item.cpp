#include "stdafx.h"
#include "item.h"

HRESULT item::init(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{

	_imagkey = imgKey;
	_imgItem = IMAGEMANAGER->findImage(imgKey);

	_x = 0;
	_y = 0;
	_cost = 0;

	_att = att;
	_def = def;
	_matt = matt;

	_kind = kind;
	_itemRect = RectMake(_x, _y, 20, 20);

	return S_OK;
}

void item::initpotion(char * imgKey, int hp, int mp, ITEM_KIND kind, int cost)
{
	_imagkey = imgKey;
	_imgItem = IMAGEMANAGER->findImage(imgKey);

	_x = 0;
	_y = 0;

	_hp = hp;
	_mp = mp;
	_kind = kind;
	_itemRect = RectMake(_x, _y, 20, 20);
}

void item::release(void)
{
}

void item::update(void)
{
}

void item::render(void)
{
	_imgItem->render(getMemDC(), _x, _y);
}

void item::setPos(float x, float y)
{
	_x = x;
	_y = y;
}