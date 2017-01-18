#include "stdafx.h"
#include "Shop.h"
#include "item.h"
#include "Owplayer.h"
#include "inventory.h"

HRESULT Shop::init(void)
{
	addItem("RongSword", 5, 0, 0, Weapon_, 120, 130, 1500);
	addItem("Excalivur", 200, 0, 0, Weapon_, 270, 130, 50000);
	addItem("Shotbow", 4, 0, 3, Weapon_, 120, 210, 1000);
	addItem("bow2", 20, 0, 25, Weapon_, 270, 210, 10000);
	addItem("mase", 6, 0, 2, Weapon_, 120, 290, 2000);
	addItem("mase2", 15, 0, 20, Weapon_, 270, 290, 7500);
	addItem("amour", 0, 10, 0, Equip_, 120, 370, 1500);
	addItem("amour2", 0, 200, 0, Equip_, 270, 370, 50000);
	addPotion("hppotion", 10, 0, Potion_, 500, 120, 450);
	addPotion("mppotion", 0, 10, Potion_, 500, 270, 450);
	_Exit = RectMake(360, 490, 20, 20);
	_shop = IMAGEMANAGER->findImage("Shoping");
	_shop->setX(100);
	_shop->setY(50);
	_isopen = false;
	_Owplayer = NULL;

	return S_OK;
}

void Shop::release(void)
{
	for (int i = 0; i < _shoplist.size(); i++)
	{
		_shoplist[i]->release();
		SAFE_DELETE(_shoplist[i]);
	}
	_shoplist.clear();
	for (int i = 0; i < _shoppotionlist.size(); i++)
	{
		_shoppotionlist[i]->release();
		SAFE_DELETE(_shoppotionlist[i]);
	}

	_shoppotionlist.clear();
}

void Shop::update(void)
{
	if (_isopen == true) {
		//(PtInRect(&_invenRect, _ptMouse)) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown('I'))





		for (int i = 0; i < _shoplist.size(); i++)
		{
			//rongsword
			if (PtInRect(&_shoplist[0]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[0]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[0]->getcost());
					_Owplayer->getinventory()->addInven("RongSword", 5, 0, 0, Weapon_, _shoplist[0]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[0]->getcost())
				{
					break;
				}
			}
			//excali
			if (PtInRect(&_shoplist[1]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[1]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[1]->getcost());
					_Owplayer->getinventory()->addInven("Excalivur", 200, 0, 0, Weapon_, _shoplist[1]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[1]->getcost())
				{
					break;
				}
			}
			//shotbow
			if (PtInRect(&_shoplist[2]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[2]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[2]->getcost());
					_Owplayer->getinventory()->addInven("Shotbow", 4, 0, 3, Weapon_, _shoplist[2]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[2]->getcost())
				{
					break;
				}
			}
			//bow2
			if (PtInRect(&_shoplist[3]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[3]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[3]->getcost());
					_Owplayer->getinventory()->addInven("bow2", 20, 0, 25, Weapon_, _shoplist[3]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[3]->getcost())
				{
					break;
				}
			}
			//mase
			if (PtInRect(&_shoplist[4]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[4]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[4]->getcost());
					_Owplayer->getinventory()->addInven("mase", _shoplist[4]->getAtt(), 0, _shoplist[4]->getMatt(), Weapon_, _shoplist[4]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[4]->getcost())
				{
					break;
				}
			}
			//mase2
			if (PtInRect(&_shoplist[5]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[5]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[5]->getcost());
					_Owplayer->getinventory()->addInven("mase2", _shoplist[5]->getAtt(), 0, _shoplist[5]->getMatt(), Weapon_, _shoplist[5]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[5]->getcost())
				{
					break;
				}
			}
			//amour
			if (PtInRect(&_shoplist[6]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[6]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[6]->getcost());
					_Owplayer->getinventory()->addEquip("amour", 0, _shoplist[6]->getDef(), 0, Equip_, _shoplist[6]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[6]->getcost())
				{
					break;
				}
			}
			//amour2
			if (PtInRect(&_shoplist[7]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoplist[7]->getcost())
				{

					_Owplayer->setMoney(_Owplayer->getMoney() - _shoplist[7]->getcost());
					_Owplayer->getinventory()->addEquip("amour2", 0, _shoplist[7]->getDef(), 0, Equip_, _shoplist[7]->getcost() / 2);
				}
				else if (_Owplayer->getMoney() < _shoplist[7]->getcost())
				{
					break;
				}
			}



		}
		//potion
		for (int i = 0; i < _shoppotionlist.size(); i++)
		{
			if (PtInRect(&_shoppotionlist[0]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoppotionlist[0]->getcost())
				{
					_Owplayer->setMoney(_Owplayer->getMoney() - _shoppotionlist[0]->getcost());
					_Owplayer->getinventory()->addpotion("hppotion", 10, 0, Potion_, _shoppotionlist[0]->getcost() / 2);
				}
			}
			else if (_Owplayer->getMoney() < _shoppotionlist[1]->getcost())
			{
				break;
			}
			if (PtInRect(&_shoppotionlist[1]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Owplayer->getMoney() >= _shoppotionlist[1]->getcost())
				{
					_Owplayer->setMoney(_Owplayer->getMoney() - _shoppotionlist[1]->getcost());
					_Owplayer->getinventory()->addpotion("mppotion", 0, 10, Potion_, _shoppotionlist[1]->getcost() / 2);
				}
			}
			else if (_Owplayer->getMoney() < _shoppotionlist[1]->getcost())
			{
				break;
			}
		}


		if (PtInRect(&_Exit, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isopen = false;
		}

	}
}

void Shop::render(void)
{
	if (_isopen)
	{
		_shop->render(getMemDC());
		/*for (int i = 0; i < _shoplist.size(); i++)
		{
		RectangleMake(getMemDC(), _shoplist[i]->getRect());
		}

		for (int i = 0; i < _shoplist.size(); i++)
		{
		_shoplist[i]->render();
		}

		*/

	}
}

void Shop::addItem(char * imgKey, int att, int def, int matt, ITEM_KIND kind, float x, float y, int cost)
{
	item* newItem = new item;
	newItem->init(imgKey, att, def, matt, kind, cost);
	newItem->setCost(cost);
	newItem->setPos(x, y);
	newItem->setAtt(att);
	newItem->setDef(def);
	newItem->setMatt(matt);
	newItem->setCost(cost);
	RECT rect;
	rect = RectMake(x, y, 20, 20);
	newItem->setRect(rect);
	_shoplist.push_back(newItem);
}

void Shop::addPotion(char * imgKey, int hp, int mp, ITEM_KIND kind, int cost, float x, float y)
{
	item* newpotion = new item;
	newpotion->initpotion(imgKey, hp, mp, kind, cost);
	newpotion->setHp(hp);
	newpotion->setMp(mp);
	newpotion->setCost(cost);
	RECT rect;
	rect = RectMake(x, y, 20, 20);
	newpotion->setRect(rect);
	_shoppotionlist.push_back(newpotion);
}

void Shop::setOwPlayer(Owplayer * player)
{
	_Owplayer = player;
}