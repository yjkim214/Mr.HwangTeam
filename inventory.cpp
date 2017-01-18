#include "stdafx.h"
#include "inventory.h"
#include "item.h"
#include "Owplayer.h"

HRESULT inventory::init(void)
{

	_inven = IMAGEMANAGER->findImage("inven");
	_invenRect = RectMakeCenter(WINSIZEX / 2 + 50, WINSIZEY - 25, 50, 50);
	_Exit = RectMakeCenter(_inven->getX() + 280, _inven->getY() + 40, 40, 40);
	_inven->setX(WINSIZEX / 2);
	_inven->setY(10);
	_isopen = false;
	_state = WEAPON;

	return S_OK;
}

void inventory::release(void)
{
}

void inventory::update(void)
{

	// 인벤토리 초기화
	_invenRect = RectMakeCenter(WINSIZEX / 2 + 50, WINSIZEY - 25, 50, 50);
	_Exit = RectMakeCenter(_inven->getX() + 180, _inven->getY() + 40, 40, 40);
	_Weapon = RectMakeCenter(_inven->getX() + 180, _inven->getY() + 80, 20, 20);
	_Equip = RectMakeCenter(_inven->getX() + 180, _inven->getY() + 120, 20, 20);
	_Potion = RectMakeCenter(_inven->getX() + 180, _inven->getY() + 150, 20, 20);
	_Quest = RectMakeCenter(_inven->getX() + 180, _inven->getY() + 180, 20, 20);

	if (_state == WEAPON) {
		for (int i = 0; i < _vinvenlist.size(); i++)
		{
			if (i < 15) {
				_vinvenlist[i]->setPos((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30);
				RECT rc;
				rc = RectMake((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30, 20, 20);
				_vinvenlist[i]->setRect(rc);
			}
		}

		if (_isShopOpen == false && _isopen == true)
		{
			for (int i = 0; i < _vinvenlist.size(); i++)
			{
				if (PtInRect(&_vinvenlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					if (_Owplayer->getCharacter() == ALEX&& _Owplayer->getWeapon() == false) {
						_Owplayer->addWeapon(_vinvenlist[i]->getkey(), _vinvenlist[i]->getAtt(), _vinvenlist[i]->getDef(), _vinvenlist[i]->getMatt(), _vinvenlist[i]->getkind(), _vinvenlist[i]->getcost());
						_Owplayer->setAlexAtt(_Owplayer->getAlexAtt() + _vinvenlist[i]->getAtt());
						_Owplayer->setWeapon(true);
						_vinvenlist.erase(_vinvenlist.begin() + i);
					}
					else if (_Owplayer->getCharacter() == TEMP&& _Owplayer->getTemWeapon() == false)
					{
						_Owplayer->addTemWeapon(_vinvenlist[i]->getkey(), _vinvenlist[i]->getAtt(), _vinvenlist[i]->getDef(), _vinvenlist[i]->getMatt(), _vinvenlist[i]->getkind(), _vinvenlist[i]->getcost());
						_Owplayer->setTemWeapon(true);
						_Owplayer->setTemAtt(_Owplayer->getTemAtt() + _vinvenlist[i]->getAtt());
						_Owplayer->setTemMatt(_Owplayer->getTemMatt() + _vinvenlist[i]->getMatt());
						_vinvenlist.erase(_vinvenlist.begin() + i);
					}
					else if (_Owplayer->getCharacter() == LUNAR && _Owplayer->getLunaWeapon() == false)
					{
						_Owplayer->addLunaWeapon(_vinvenlist[i]->getkey(), _vinvenlist[i]->getAtt(), _vinvenlist[i]->getDef(), _vinvenlist[i]->getMatt(), _vinvenlist[i]->getkind(), _vinvenlist[i]->getcost());
						_Owplayer->setLunaWeapon(true);
						_Owplayer->setLunaAtt(_Owplayer->getLunaAtt() + _vinvenlist[i]->getAtt());
						_Owplayer->setLunaMatt(_Owplayer->getLunaMatt() + _vinvenlist[i]->getMatt());
						_vinvenlist.erase(_vinvenlist.begin() + i);
					}
				}
			}
		}

		if (_isShopOpen == true && _isopen == true)
		{
			for (int i = 0; i < _vinvenlist.size(); i++)
			{
				if (PtInRect(&_vinvenlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_Owplayer->setMoney(_Owplayer->getMoney() + _vinvenlist[i]->getcost());
					_vinvenlist.erase(_vinvenlist.begin() + i);
				}
			}
		}

		if (PtInRect(&_Equip, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(1);
			_state = EQUIP;
		}
		if (PtInRect(&_Potion, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(2);
			_state = POTION;
		}
		if (PtInRect(&_Quest, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(3);
			_state = QUEST;
		}

	}
	// EQUIP =============================
	if (_state == EQUIP)
	{
		for (int i = 0; i < _vEquiplist.size(); i++)
		{
			if (i < 15) {
				_vEquiplist[i]->setPos((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30);
				RECT rc;
				rc = RectMake((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30, 20, 20);
				_vEquiplist[i]->setRect(rc);
			}
		}

		if (_isShopOpen == false && _isopen == true)
		{
			for (int i = 0; i < _vEquiplist.size(); i++)
			{
				if (PtInRect(&_vEquiplist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					if (_Owplayer->getCharacter() == ALEX&& _Owplayer->getEquip() == false)
					{
						_Owplayer->addEquip(_vEquiplist[i]->getkey(), _vEquiplist[i]->getAtt(), _vEquiplist[i]->getDef(), _vEquiplist[i]->getMatt(), _vEquiplist[i]->getkind(), _vEquiplist[i]->getcost());
						_Owplayer->setEquip(true);
						_Owplayer->setAlexDef(_Owplayer->getAlexDef() + _vEquiplist[i]->getDef());
						_vEquiplist.erase(_vEquiplist.begin() + i);
					}
					else if (_Owplayer->getCharacter() == TEMP&& _Owplayer->getTemEquip() == false)
					{
						_Owplayer->addTemEquip(_vEquiplist[i]->getkey(), _vEquiplist[i]->getAtt(), _vEquiplist[i]->getDef(), _vEquiplist[i]->getMatt(), _vEquiplist[i]->getkind(), _vEquiplist[i]->getcost());
						_Owplayer->setTemEquip(true);
						_Owplayer->setTemDef(_Owplayer->getTemDef() + _vEquiplist[i]->getDef());
						_vEquiplist.erase(_vEquiplist.begin() + i);
					}
					else if (_Owplayer->getCharacter() == LUNAR&&_Owplayer->getLunaEquip() == false)
					{
						_Owplayer->addLunaEquip(_vEquiplist[i]->getkey(), _vEquiplist[i]->getAtt(), _vEquiplist[i]->getDef(), _vEquiplist[i]->getMatt(), _vEquiplist[i]->getkind(), _vEquiplist[i]->getcost());
						_Owplayer->setLunaEquip(true);
						_Owplayer->setLunaDef(_Owplayer->getLunaDef() + _vEquiplist[i]->getDef());
						_vEquiplist.erase(_vEquiplist.begin() + i);
					}
				}
			}
		}
		if (_isShopOpen == true && _isopen == true)
		{
			for (int i = 0; i < _vEquiplist.size(); i++)
			{
				if (PtInRect(&_vEquiplist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_Owplayer->setMoney(_Owplayer->getMoney() + _vEquiplist[i]->getcost());
					_vEquiplist.erase(_vEquiplist.begin() + i);
				}
			}
		}

		if (PtInRect(&_Weapon, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(0);
			_state = WEAPON;
		}
		if (PtInRect(&_Potion, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(2);
			_state = POTION;
		}
		if (PtInRect(&_Quest, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(3);
			_state = QUEST;
		}

	}
	//potion
	if (_state == POTION)
	{

		for (int i = 0; i < _vpotionlist.size(); i++)
		{
			if (i < 15) {
				_vpotionlist[i]->setPos((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30);
				RECT rc;
				rc = RectMake((_inven->getX() + 18) + (i % 5) * 28, (_inven->getY() + 70) + (i / 5) * 30, 20, 20);
				_vpotionlist[i]->setRect(rc);
			}
		}


		if (_isShopOpen == false && _isopen == true)
		{
			for (int i = 0; i < _vpotionlist.size(); i++)
			{
				if (PtInRect(&_vpotionlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					if (_Owplayer->getCharacter() == ALEX)
					{
						_Owplayer->setAlexcurrenthp(_Owplayer->getAlexcurrenthp() + _vpotionlist[i]->getHp());
						_Owplayer->setAlexcurrentMp(_Owplayer->getAlexcurrentMp() + _vpotionlist[i]->getMp());
						_vpotionlist.erase(_vpotionlist.begin() + i);

					}
					else if (_Owplayer->getCharacter() == TEMP)
					{
						_Owplayer->setTemcurrenthp(_Owplayer->getTemcurrenthp() + _vpotionlist[i]->getHp());
						_Owplayer->setTemcurrentmp(_Owplayer->getTemcurrentmp() + _vpotionlist[i]->getMp());
						_vpotionlist.erase(_vpotionlist.begin() + i);
					}
					else if (_Owplayer->getCharacter() == LUNAR)
					{
						_Owplayer->setLunacurrenthp(_Owplayer->getLunacurrenthp() + _vpotionlist[i]->getHp());
						_Owplayer->setLunacurrentmp(_Owplayer->getLunacurrentmp() + _vpotionlist[i]->getMp());
						_vpotionlist.erase(_vpotionlist.begin() + i);
					}
				}
			}
		}
		if (_isShopOpen == true && _isopen == true)
		{
			for (int i = 0; i < _vpotionlist.size(); i++)
			{
				if (PtInRect(&_vpotionlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_Owplayer->setMoney(_Owplayer->getMoney() + _vpotionlist[i]->getcost());
					_vpotionlist.erase(_vpotionlist.begin() + i);
				}
			}
		}



		if (PtInRect(&_Weapon, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(0);
			_state = WEAPON;
		}
		if (PtInRect(&_Equip, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(1);
			_state = EQUIP;
		}
		if (PtInRect(&_Quest, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(3);
			_state = QUEST;
		}

	}
	if (_state == QUEST)
	{
		if (PtInRect(&_Weapon, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(0);
			_state = WEAPON;
		}
		if (PtInRect(&_Equip, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(1);
			_state = EQUIP;
		}
		if (PtInRect(&_Potion, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inven->setFrameX(2);
			_state = POTION;
		}

	}

	if ((PtInRect(&_invenRect, _ptMouse)) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown('I'))
	{
		if (_isopen == false)
		{
			_inven->setX(WINSIZEX / 2);
			_inven->setY(10);

			_isopen = true;
			_state = WEAPON;
			_inven->setFrameX(0);
		}
		else if (_isopen == true)
		{
			_isopen = false;
		}
	}





	//Exit 를  눌러서 인벤토리 삭제하기

	if ((PtInRect(&_Exit, _ptMouse)) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_isopen == true) { _isopen = false; }
	}

	if (PtInRect(&_inven->boundingBoxWithFrame(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ptPrevX = _ptMouse.x;
		_ptPrevY = _ptMouse.y;
	}

	if (PtInRect(&_inven->boundingBoxWithFrame(), _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		int intervalX = _ptMouse.x - _ptPrevX;
		int intervalY = _ptMouse.y - _ptPrevY;

		_inven->setX(_inven->getX() + intervalX);
		_inven->setY(_inven->getY() + intervalY);

		_ptPrevX = _ptMouse.x;
		_ptPrevY = _ptMouse.y;
	}

	// 인벤토리 나오게끔 하기


}

void inventory::render(void)
{
	char dir[256];
	wsprintf(dir, "%d", _isopen && _isShopOpen);
	TextOut(getMemDC(), 0, 0, dir, strlen(dir));



	if (_isopen == true)
	{
		_inven->frameRender(getMemDC(), _inven->getX(), _inven->getY());
		/*Rectangle(getMemDC(), _Exit.left, _Exit.top, _Exit.right, _Exit.bottom);
		RectangleMake(getMemDC(), _Equip);
		RectangleMake(getMemDC(), _Weapon);
		RectangleMake(getMemDC(), _Potion);
		RectangleMake(getMemDC(), _Quest);*/
		char str[256];
		//글자배경모드
		SetBkMode(getMemDC(), TRANSPARENT);
		//글자색상
		SetTextColor(getMemDC(), RGB(219, 192, 0));
		//출력
		wsprintf(str, "%d", _Owplayer->getMoney());
		TextOut(getMemDC(), _inven->getX() + 40, _inven->getY() + 190, str, strlen(str));






		if (_state == WEAPON)
		{
			for (int i = 0; i < _vinvenlist.size(); i++)
			{
				_vinvenlist[i]->render();
				//RectangleMake(getMemDC(), _vinvenlist[i]->getRect());
			}
		}
		if (_state == EQUIP)
		{
			for (int i = 0; i < _vEquiplist.size(); i++)
			{
				_vEquiplist[i]->render();
				//RectangleMake(getMemDC(), _vEquiplist[i]->getRect());
			}
		}
		if (_state == POTION)
		{
			for (int i = 0; i < _vpotionlist.size(); i++)
			{
				_vpotionlist[i]->render();
			}
		}

	}
}

void inventory::addInven(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newinven = new item;
	newinven->init(imgKey, att, def, matt, kind, cost);
	newinven->setkey(imgKey);
	newinven->setCost(cost);
	newinven->setAtt(att);
	newinven->setDef(def);
	newinven->setMatt(matt);
	_vinvenlist.push_back(newinven);
}

void inventory::addEquip(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newequip = new item;
	newequip->init(imgKey, att, def, matt, kind, cost);
	newequip->setkey(imgKey);
	newequip->setCost(cost);
	newequip->setAtt(att);
	newequip->setDef(def);
	newequip->setMatt(matt);
	_vEquiplist.push_back(newequip);

}

void inventory::addpotion(char * imgKey, int hp, int mp, ITEM_KIND kind, int cost)
{
	item* newpoti = new item;
	newpoti->initpotion(imgKey, hp, mp, kind, cost);
	newpoti->setHp(hp);
	newpoti->setMp(mp);
	newpoti->setCost(cost);
	_vpotionlist.push_back(newpoti);
}

void inventory::setOwPlayer(Owplayer * player)
{
	_Owplayer = player;
}
