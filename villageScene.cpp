#include "stdafx.h"
#include "villageScene.h"
#include "inventory.h"
HRESULT villageScene::init(void)
{
	_villageMap = new villageMap;
	_villageMap->init();

	_Owplayer = new Owplayer;
	_Owplayer->init();

	_Shop = new Shop;
	_Shop->init();
	_Shop->setOwPlayer(_Owplayer);

	_npc = new NPC;
	_npc->init();


	_villageMap->setOWPlayer(_Owplayer);
	_Owplayer->setScene(_villageMap);
	_npc->setRefer(_villageMap, _Owplayer);
	_Owplayer->setnpc(_npc);
	SOUNDMANAGER->play("villageMusic");


	//SOUNDMANAGER->play("마을ver2");
	time = 0;

	return S_OK;
}

void villageScene::release(void)
{
	_villageMap->release();
	SAFE_DELETE(_villageMap);

	_Owplayer->release();
	SAFE_DELETE(_Owplayer);

	_Shop->release();
	SAFE_DELETE(_Shop);
	_npc->release();
	SAFE_DELETE(_npc);
}

void villageScene::update(void)
{


	_Owplayer->getinventory()->isShopOpen(_Shop->getIsOpen());

	
	RECT _ARC;
	if (IntersectRect(&_ARC,&_npc->shopCrashRc(),&_Owplayer->getPlayerImg()->boundingBoxWithFrame())&&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_Shop->getIsOpen())
		{
			_npc->setState(MOVE);
			_Shop->closeShop();
		}

		else
		{
			_npc->setState(STOP);
			_Shop->openShop();
			
		}
	}

	

	time++;

	if (_villageMap->getState() == VILLAGE)
	{
		if (time < 10)
		{
			_Owplayer->setX(PLAYERDATA->getPlayerX());
			_Owplayer->setY(PLAYERDATA->getPlayerY());
			_villageMap->setBgX(PLAYERDATA->getBgX());
			_villageMap->setBgY(PLAYERDATA->getBgY());
			_npc->setX(PLAYERDATA->getNpcX(), 0);
			_npc->setY(PLAYERDATA->getNpcY(), 0);
		}
		if (SOUNDMANAGER->isPlaySound("dungeonSound"))
		{
			SOUNDMANAGER->stop("dungeonSound");
			SOUNDMANAGER->play("villageMusic");
		}
		if (SOUNDMANAGER->isPlaySound("bossRoomSound"))
		{
			SOUNDMANAGER->stop("bossRoomSound");
			SOUNDMANAGER->play("villageMusic");
		}
	}

	if (_villageMap->getState() == DUNGEON)
	{
		PLAYERDATA->setSlimeDie(false);
		PLAYERDATA->setFluffyBugDie(false);
		PLAYERDATA->setFlytrapperDie(false);
		PLAYERDATA->setBarbarianDie(false);
		PLAYERDATA->setDevilBomberDie(false);
		PLAYERDATA->setMonsterX(100);
		PLAYERDATA->setMonsterY(150);
		PLAYERDATA->setBackX(0);
		PLAYERDATA->setBackY(0);
		PLAYERDATA->setSlimeX(279);
		PLAYERDATA->setSlimeY(619);
		PLAYERDATA->setFluffyBugX(411);
		PLAYERDATA->setFluffyBugY(1037);
		PLAYERDATA->setFlytrapperX(1420);
		PLAYERDATA->setFlytrapperY(1018);
		PLAYERDATA->setBarbarianX(711);
		PLAYERDATA->setBarbarianY(253);
		PLAYERDATA->setDevilBomberX(1191);
		PLAYERDATA->setDevilBomberY(219);
		PLAYERDATA->setPlayerX(532);
		PLAYERDATA->setPlayerY(435);
		PLAYERDATA->setBgX(210);
		PLAYERDATA->setBgY(603);
		PLAYERDATA->setNpcX(545);
		PLAYERDATA->setNpcY(-5);
		if (SOUNDMANAGER->isPlaySound("villageMusic"))
		{
			SOUNDMANAGER->stop("villageMusic");
			/*SOUNDMANAGER->play("dungeonSound");*/
		}
		_Owplayer->saveData();
		SCENEMANAGER->changeScene("던전");
	}
	if (_villageMap->getState() == BOSSROOM)
	{
		COLORREF colorU = GetPixel(_villageMap->getPixelBoss()->getMemDC(), _Owplayer->getX() + 15, _villageMap->getBgY() + _Owplayer->getProveUp());
		int rU = GetRValue(colorU);
		int gU = GetGValue(colorU);
		int bU = GetBValue(colorU);
		if (rU == 0 && gU == 255 && bU == 0)
		{
			PLAYERDATA->setMonsterNumber(6);
			SOUNDMANAGER->stop("bossRoomSound");
			SCENEMANAGER->changeScene("배틀화면");
		}
		if (SOUNDMANAGER->isPlaySound("villageMusic"))
		{
			SOUNDMANAGER->stop("villageMusic");
			SOUNDMANAGER->play("bossRoomSound");
		}
	}
	_villageMap->update();
	_Owplayer->update();
	_Shop->update();
	_npc->update();
	Load();


}

void villageScene::render(void)
{
	_villageMap->render();
	_Owplayer->render();
	_npc->render();


	if (_villageMap->getState() == VILLAGE)
	{
		IMAGEMANAGER->alphaRender("village_building", getMemDC(), 0, 0, _villageMap->getBgX(), _villageMap->getBgY(),
			1600 - _villageMap->getBgX(), 1200 - _villageMap->getBgY(), 100);
		IMAGEMANAGER->alphaRender("village_in", getMemDC(), 0, 0, _villageMap->getBgX(), _villageMap->getBgY(),
			1600 - _villageMap->getBgX(), 1200 - _villageMap->getBgY(), 100);
	}

	if (_villageMap->getState() == DUNGEON)
	{
		IMAGEMANAGER->alphaRender("dungeon_tree", getMemDC(), 0, 0, _villageMap->getBgX(), _villageMap->getBgY(),
			1600 - _villageMap->getBgX(), 1200 - _villageMap->getBgY(), 100);
	}

	_Owplayer->invenrender();
	_Shop->render();
	_npc->chatRender();
	_villageMap->menuRender();
}
void villageScene::Load()
{
	if (_mainMenu->getIsLoading() == true)
	{
		if (time < 10)
		{
			_villageMap->setState(INIDATA->loadDataInteger("RunarSilverStorySave", "VILLAGEMAP", "villageMapState"));
			_villageMap->setBgX(INIDATA->loadDataInteger("RunarSilverStorySave", "VILLAGEMAP", "villageMapBgX"));
			_villageMap->setBgY(INIDATA->loadDataInteger("RunarSilverStorySave", "VILLAGEMAP", "villageMapBgY"));
			_Owplayer->setX(INIDATA->loadDataInteger("RunarSilverStorySave", "PLAYER", "playerX"));
			_Owplayer->setY(INIDATA->loadDataInteger("RunarSilverStorySave", "PLAYER", "playerY"));
			//INIDATA->loadDataInteger("RunarSilverStorySave", "PLAYER", "playerAtt");
			//INIDATA->loadDataInteger("RunarSilverStorySave", "PLAYER", "playerDex");
		}
	}
}