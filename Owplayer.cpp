#include "stdafx.h"
#include "Owplayer.h"
#include "villageMap.h"
#include "inventory.h"
#include "item.h"
#include "progressBar.h"
#include "NPC.h"

HRESULT Owplayer::init(void)
{

	_inventory = new inventory;
	_inventory->init();


	_hp = new progressBar;
	_hp->init("uihpbarfront", "uihpbarback", 180, 470, 145, 23);

	_mp = new progressBar;
	_mp->init("uimpbarfront", "uihpbarback", 180, 525, 145, 23);
	_inventory->setOwPlayer(this);
	_shopopen = false;

	_playerImg = IMAGEMANAGER->findImage("owPlayer_idle");
	_statusimg = IMAGEMANAGER->findImage("status");
	_statusmenuimg = IMAGEMANAGER->findImage("statusmenu");
	_statusmenuimg->setX(WINSIZEX / 2);
	_statusmenuimg->setY(WINSIZEY / 2);

	//alex hp 
	_AlexcurrentHp = 80;
	_AlexMaxHp = 100;

	_AlexcurrentMp = 100;
	_AlexMaxMp = 100;

	_AlexAtt = 5;
	_AlexDef = 10;
	_AlexMatt = 0;


	//temp hp

	_TemcurrentHp = 100;
	_TemcurrentMp = 100;
	_TemMaxHp = 100;
	_TemMaxMp = 100;

	_TemAtt = 8;
	_TemDef = 5;
	_TemMatt = 2;
	// luna hp

	_LunaAtt = 3;
	_LunaDef = 5;
	_LunaMatt = 8;

	_lunacurrentHp = 100;
	_lunaMaxHp = 100;
	_lunacurrentMp = 50;
	_lunaMaxMp = 100;

	//
	_statusimg->setX(0);
	_statusimg->setY(400);
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_speed = 3.0f;
	_state = IDLE;
	_lookat = DOWN;
	_animcount = 0;
	_money = 3000;
	_isWeapon = false;
	_isEquip = false;
	_isTemWeapon = false;
	_isTemEquip = false;
	_islunaWeapon = false;
	_islunaEquip = false;
	_character = ALEX;
	_proveLeft = _x - _playerImg->getFrameWidth() / 15;
	_proveRight = _x + _playerImg->getFrameWidth() - 15;
	_proveUp = _y + _playerImg->getFrameHeight() - 40;
	_proveDown = _y + _playerImg->getFrameHeight() - 15;

	return S_OK;
}

void Owplayer::release(void)
{
}

void Owplayer::update(void)
{
	playerstate();
	playersetstate();
	animation();
	_hp->update();
	_mp->update();
	_playerImg->setX(_x);
	_playerImg->setY(_y);



	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_money += 10000;
		
	}
	RECT _crush;
	if (IntersectRect(&_crush, &_npc->shopCrashRc(), &_playerImg->boundingBoxWithFrame()) && KEYMANAGER->isOnceKeyDown(VK_SPACE) && _shopopen == false)
	{
		_npc->setState(STOP);
		_shopopen = true;
	}


	if (KEYMANAGER->isToggleKey('J'))
	{
		MenuUpdate();
	}

	//CHARACTER CHANGE
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (_character == ALEX) {
			_character = TEMP;
			_playerImg = IMAGEMANAGER->findImage("owtem_idle");

		}
		else if (_character == TEMP)
		{
			_character = LUNAR;
			_playerImg = IMAGEMANAGER->findImage("owluna_idle");
		}
		else if (_character == LUNAR)
		{
			_character = ALEX;
			_playerImg = IMAGEMANAGER->findImage("owPlayer_idle");
		}
	}


	if (_character == ALEX)
	{

		_statusimg = IMAGEMANAGER->findImage("status");
		_hp->setGauge((float)_AlexcurrentHp, (float)_AlexMaxHp);
		_mp->setGauge((float)_AlexcurrentMp, (float)_AlexMaxMp);
		_statusimg->setX(0);
		_statusimg->setY(400);
		if (_AlexcurrentHp > _AlexMaxHp)
		{
			_AlexcurrentHp = _AlexMaxHp;
		}
		if (_AlexcurrentMp > _AlexMaxMp)
		{
			_AlexcurrentMp = _AlexMaxMp;
		}
	}
	else if (_character == TEMP)
	{

		_statusimg = IMAGEMANAGER->findImage("statustem");
		_hp->setGauge((float)_TemcurrentHp, (float)_TemMaxHp);
		_mp->setGauge((float)_TemcurrentMp, (float)_TemMaxMp);
		_statusimg->setX(0);
		_statusimg->setY(400);
		if (_TemcurrentHp > _TemMaxHp)
		{
			_TemcurrentHp = _TemMaxHp;
		}
		if (_TemcurrentMp > _TemMaxMp)
		{
			_TemcurrentMp = _TemMaxMp;
		}
	}
	else if (_character == LUNAR)
	{

		_statusimg = IMAGEMANAGER->findImage("statusluna");
		_hp->setGauge((float)_lunacurrentHp, (float)_lunaMaxHp);
		_mp->setGauge((float)_lunacurrentMp, (float)_lunaMaxMp);
		_statusimg->setX(0);
		_statusimg->setY(400);
		if (_lunacurrentHp > _lunaMaxHp)
		{
			_lunacurrentHp = _lunaMaxHp;
		}
		if (_lunacurrentMp > _lunaMaxMp)
		{
			_lunacurrentMp = _lunaMaxMp;
		}
	}


	if (_inventory->getIsOpen() == true)
	{

		if (_character == ALEX)
		{
			equipstate();

		}

		else if (_character == TEMP)
		{
			temequipstate();

		}

		else if (_character == LUNAR)
		{
			lunaequipstate();

		}

	}

	ProveUpdate();
	_inventory->update();
}

void Owplayer::render(void)
{
	_playerImg->frameRender(getMemDC(), _x, _y);




	if (KEYMANAGER->isToggleKey('0'))
	{
		Rectangle(getMemDC(), _camera.left, _camera.top, _camera.right, _camera.bottom);
	}




}

void Owplayer::invenrender(void)
{
	_inventory->render();
	if (_inventory->getIsOpen() == true) {
		if (_character == ALEX) {

			for (int i = 0; i < _vWeaponlist.size(); i++)
			{
				_vWeaponlist[i]->render();
			}

			for (int i = 0; i < _vIEquiplist.size(); i++)
			{
				_vIEquiplist[i]->render();
			}

		}

		else if (_character == TEMP)
		{

			for (int i = 0; i < _vTemWeaponlist.size(); i++)
			{
				_vTemWeaponlist[i]->render();
			}

			for (int i = 0; i < _vTemEquiplist.size(); i++)
			{
				_vTemEquiplist[i]->render();
			}

		}
		else if (_character == LUNAR)
		{
			for (int i = 0; i < _vLunaWeaponlist.size(); i++)
			{
				_vLunaWeaponlist[i]->render();
			}
			for (int i = 0; i < _vLunaEquiplist.size(); i++)
			{
				_vLunaEquiplist[i]->render();
			}
		}

	}

if (KEYMANAGER->isToggleKey('J'))
	{
		OpenMenu();
		Font();
	}


	_statusimg->render(getMemDC());


	_hp->render();
	_mp->render();
}



//==================================================================================
//  1. Player Update : 
// ==================================================================

void Owplayer::playerstate()
{
	_camera = RectMakeCenter(_x, _y, 500, 400);
	if (_state == MOVE_LEFT)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_lookat = LEFT;
		}
	}

	if (_state == MOVE_RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_lookat = RIGHT;
		}

	}

	if (_state == MOVE_UP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{

			_lookat = UP;
		}
	}

	if (_state == MOVE_DOWN)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{

			_lookat = DOWN;
		}
	}

}

void Owplayer::playersetstate()
{

	if (_character == ALEX)
	{
		if (_state == IDLE)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_playerImg = IMAGEMANAGER->findImage("owPlayer_move");
				_state = MOVE_LEFT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_playerImg = IMAGEMANAGER->findImage("owPlayer_move");
				_state = MOVE_RIGHT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_playerImg = IMAGEMANAGER->findImage("owPlayer_move");
				_state = MOVE_UP;
			}

			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owPlayer_move");
				_state = MOVE_DOWN;
			}
		}


		if (_state == MOVE_LEFT || _state == MOVE_RIGHT || _state == MOVE_UP || _state == MOVE_DOWN)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owPlayer_idle");
				_state = IDLE;
			}
		}
	}
	// TEMP
	if (_character == TEMP)
	{
		if (_state == IDLE)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_playerImg = IMAGEMANAGER->findImage("owtem_move");
				_state = MOVE_LEFT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_playerImg = IMAGEMANAGER->findImage("owtem_move");
				_state = MOVE_RIGHT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_playerImg = IMAGEMANAGER->findImage("owtem_move");
				_state = MOVE_UP;
			}

			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owtem_move");
				_state = MOVE_DOWN;
			}
		}


		if (_state == MOVE_LEFT || _state == MOVE_RIGHT || _state == MOVE_UP || _state == MOVE_DOWN)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owtem_idle");
				_state = IDLE;
			}
		}
	}


	// Luna
	if (_character == LUNAR)
	{
		if (_state == IDLE)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_playerImg = IMAGEMANAGER->findImage("owluna_move");
				_state = MOVE_LEFT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_playerImg = IMAGEMANAGER->findImage("owluna_move");
				_state = MOVE_RIGHT;
			}

			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_playerImg = IMAGEMANAGER->findImage("owluna_move");
				_state = MOVE_UP;
			}

			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owluna_move");
				_state = MOVE_DOWN;
			}
		}


		if (_state == MOVE_LEFT || _state == MOVE_RIGHT || _state == MOVE_UP || _state == MOVE_DOWN)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				_playerImg = IMAGEMANAGER->findImage("owluna_idle");
				_state = IDLE;
			}
		}
	}


}

void Owplayer::animation()
{
	if (_state == IDLE)
	{
		_playerImg->setFrameX(static_cast<int>(_lookat));
	}

	if (_state == MOVE_LEFT || _state == MOVE_RIGHT || _state == MOVE_UP || _state == MOVE_DOWN)
	{
		_animcount++;
		_playerImg->setFrameY(static_cast<int>(_lookat));
		if (_animcount % 10 == 0)
		{
			_playerImg->setFrameX(_playerImg->getFrameX() + 1);
			if (_playerImg->getFrameX() >= _playerImg->getMaxFrameX())
			{
				_playerImg->setFrameX(0);
			}

			_animcount = 0;
		}
	}
}


void Owplayer::ProveUpdate()
{
	_proveLeft = _x - _playerImg->getFrameWidth() / 15;
	_proveRight = _x + _playerImg->getFrameWidth() - 15;
	_proveUp = _y + _playerImg->getFrameHeight() - 40;
	_proveDown = _y + _playerImg->getFrameHeight() - 15;
}

//alex
void Owplayer::addWeapon(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	/*item* newinven = new item;
	newinven->init(imgKey, att, def, matt, kind, cost);
	newinven->setCost(cost);
	_vinvenlist.push_back(newinven);*/
	item* newWeapon = new item;
	newWeapon->init(imgKey, att, def, matt, kind, cost);
	newWeapon->setAtt(att);
	newWeapon->setDef(def);
	newWeapon->setMatt(matt);
	newWeapon->setCost(cost);
	_vWeaponlist.push_back(newWeapon);


}

void Owplayer::addEquip(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newEquip = new item;
	newEquip->init(imgKey, att, def, matt, kind, cost);
	newEquip->setAtt(att);
	newEquip->setDef(def);
	newEquip->setMatt(matt);
	newEquip->setCost(cost);
	_vIEquiplist.push_back(newEquip);
}

void Owplayer::addTemWeapon(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newTemWeapon = new item;
	newTemWeapon->init(imgKey, att, def, matt, kind, cost);
	newTemWeapon->setAtt(att);
	newTemWeapon->setDef(def);
	newTemWeapon->setMatt(matt);
	newTemWeapon->setCost(cost);
	_vTemWeaponlist.push_back(newTemWeapon);
}

void Owplayer::addTemEquip(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newTemEquip = new item;
	newTemEquip->init(imgKey, att, def, matt, kind, cost);
	newTemEquip->setAtt(att);
	newTemEquip->setDef(def);
	newTemEquip->setMatt(matt);
	newTemEquip->setCost(cost);
	_vTemEquiplist.push_back(newTemEquip);
}

void Owplayer::addLunaWeapon(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newLunaWeapon = new item;
	newLunaWeapon->init(imgKey, att, def, matt, kind, cost);
	newLunaWeapon->setAtt(att);
	newLunaWeapon->setDef(def);
	newLunaWeapon->setMatt(matt);
	newLunaWeapon->setCost(cost);
	_vLunaWeaponlist.push_back(newLunaWeapon);
}

void Owplayer::addLunaEquip(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost)
{
	item* newLunaEquip = new item;
	newLunaEquip->init(imgKey, att, def, matt, kind, cost);
	newLunaEquip->setAtt(att);
	newLunaEquip->setDef(def);
	newLunaEquip->setMatt(matt);
	newLunaEquip->setCost(cost);
	_vLunaEquiplist.push_back(newLunaEquip);
}

void Owplayer::OpenMenu()
{

	_statusmenuimg->render(getMemDC());

}

void Owplayer::MenuUpdate()
{
	if (PtInRect(&_statusmenuimg->boundingBox(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ptPrevX = _ptMouse.x;
		_ptPrevY = _ptMouse.y;
	}

	if (PtInRect(&_statusmenuimg->boundingBox(), _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		int intervalX = _ptMouse.x - _ptPrevX;
		int intervalY = _ptMouse.y - _ptPrevY;

		_statusmenuimg->setX(_statusmenuimg->getX() + intervalX);
		_statusmenuimg->setY(_statusmenuimg->getY() + intervalY);

		_ptPrevX = _ptMouse.x;
		_ptPrevY = _ptMouse.y;
	}
}

void Owplayer::Font()
{
	char str[256];
	//글자배경모드
	SetBkMode(getMemDC(), TRANSPARENT);
	//글자색상
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	//출력
	if (_character == ALEX) {
		sprintf(str, "%d", _AlexAtt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 90, str, strlen(str));
		sprintf(str, "%d", _AlexDef);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 130, str, strlen(str));
		sprintf(str, "%d", _AlexMatt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 170, str, strlen(str));
	}
	else if (_character == TEMP)
	{

		sprintf(str, "%d", _TemAtt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 90, str, strlen(str));
		sprintf(str, "%d", _TemDef);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 130, str, strlen(str));
		sprintf(str, "%d", _TemMatt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 170, str, strlen(str));
	}
	else if (_character == LUNAR)
	{
		sprintf(str, "%d", _LunaAtt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 90, str, strlen(str));
		sprintf(str, "%d", _LunaDef);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 130, str, strlen(str));
		sprintf(str, "%d", _LunaMatt);
		TextOut(getMemDC(), _statusmenuimg->getX() + 100, _statusmenuimg->getY() + 170, str, strlen(str));
	}
}




//temp


//alex
void Owplayer::equipstate(void)
{

	for (int i = 0; i < _vWeaponlist.size(); i++)
	{
		_vWeaponlist[i]->setPos(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250, 20, 20);
		_vWeaponlist[i]->setRect(rc);

	}


	for (int i = 0; i < _vWeaponlist.size(); i++)
	{
		if (PtInRect(&_vWeaponlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{

			_inventory->addInven(_vWeaponlist[i]->getkey(), _vWeaponlist[i]->getAtt(), _vWeaponlist[i]->getDef(), _vWeaponlist[i]->getMatt(), _vWeaponlist[i]->getkind(), _vWeaponlist[i]->getcost());
			_AlexAtt -= _vWeaponlist[i]->getAtt();
			_vWeaponlist.erase(_vWeaponlist.begin() + i);
			_isWeapon = false;
		}
	}

	//Equipe
	for (int i = 0; i < _vIEquiplist.size(); i++)
	{
		_vIEquiplist[i]->setPos(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255, 20, 20);
		_vIEquiplist[i]->setRect(rc);
	}
	for (int i = 0; i < _vIEquiplist.size(); i++)
	{
		if (PtInRect(&_vIEquiplist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inventory->addEquip(_vIEquiplist[i]->getkey(), _vIEquiplist[i]->getAtt(), _vIEquiplist[i]->getDef(), _vIEquiplist[i]->getMatt(), _vIEquiplist[i]->getkind(), _vIEquiplist[i]->getcost());
			_AlexDef -= _vIEquiplist[i]->getDef();
			_vIEquiplist.erase(_vIEquiplist.begin() + i);
			_isEquip = false;
		}
	}
}

void Owplayer::temequipstate(void)
{

	for (int i = 0; i < _vTemWeaponlist.size(); i++)
	{
		_vTemWeaponlist[i]->setPos(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250, 20, 20);
		_vTemWeaponlist[i]->setRect(rc);
	}

	for (int i = 0; i < _vTemWeaponlist.size(); i++)
	{
		if (PtInRect(&_vTemWeaponlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inventory->addInven(_vTemWeaponlist[i]->getkey(), _vTemWeaponlist[i]->getAtt(), _vTemWeaponlist[i]->getDef(), _vTemWeaponlist[i]->getMatt(), _vTemWeaponlist[i]->getkind(), _vTemWeaponlist[i]->getcost());
			_TemAtt -= _vTemWeaponlist[i]->getAtt();
			_TemMatt -= _vTemWeaponlist[i]->getMatt();
			_vTemWeaponlist.erase(_vTemWeaponlist.begin() + i);
			_isTemWeapon = false;
		}
	}


	//Equipe
	for (int i = 0; i < _vTemEquiplist.size(); i++)
	{
		_vTemEquiplist[i]->setPos(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255, 20, 20);
		_vTemEquiplist[i]->setRect(rc);
	}
	for (int i = 0; i < _vTemEquiplist.size(); i++)
	{
		if (PtInRect(&_vTemEquiplist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inventory->addEquip(_vTemEquiplist[i]->getkey(), _vTemEquiplist[i]->getAtt(), _vTemEquiplist[i]->getDef(), _vTemEquiplist[i]->getMatt(), _vTemEquiplist[i]->getkind(), _vTemEquiplist[i]->getcost());
			_TemDef -= _vTemEquiplist[i]->getDef();
			_vTemEquiplist.erase(_vTemEquiplist.begin() + i);
			_isTemEquip = false;
		}
	}

}

void Owplayer::lunaequipstate(void)
{


	for (int i = 0; i < _vLunaWeaponlist.size(); i++)
	{
		_vLunaWeaponlist[i]->setPos(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 15, _inventory->getinvenimg()->getY() + 250, 20, 20);
		_vLunaWeaponlist[i]->setRect(rc);
	}

	for (int i = 0; i < _vLunaWeaponlist.size(); i++)
	{
		if (PtInRect(&_vLunaWeaponlist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inventory->addInven(_vLunaWeaponlist[i]->getkey(), _vLunaWeaponlist[i]->getAtt(), _vLunaWeaponlist[i]->getDef(), _vLunaWeaponlist[i]->getMatt(), _vLunaWeaponlist[i]->getkind(), _vLunaWeaponlist[i]->getcost());
			_LunaAtt -= _vLunaWeaponlist[i]->getAtt();
			_LunaMatt -= _vLunaWeaponlist[i]->getMatt();
			_vLunaWeaponlist.erase(_vLunaWeaponlist.begin() + i);
			_islunaWeapon = false;
		}
	}



	//Equipe
	for (int i = 0; i < _vLunaEquiplist.size(); i++)
	{
		_vLunaEquiplist[i]->setPos(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255);
		RECT rc;
		rc = RectMake(_inventory->getinvenimg()->getX() + 70, _inventory->getinvenimg()->getY() + 255, 20, 20);
		_vLunaEquiplist[i]->setRect(rc);
	}
	for (int i = 0; i < _vLunaEquiplist.size(); i++)
	{
		if (PtInRect(&_vLunaEquiplist[i]->getRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_inventory->addEquip(_vLunaEquiplist[i]->getkey(), _vLunaEquiplist[i]->getAtt(), _vLunaEquiplist[i]->getDef(), _vLunaEquiplist[i]->getMatt(), _vLunaEquiplist[i]->getkind(), _vLunaEquiplist[i]->getcost());
			_LunaDef -= _vLunaEquiplist[i]->getDef();
			_vLunaEquiplist.erase(_vLunaEquiplist.begin() + i);
			_islunaEquip = false;
		}
	}


}
