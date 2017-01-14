#include "stdafx.h"
#include "villageScene.h"

HRESULT villageScene::init(void)
{
	_villageMap = new villageMap;
	_villageMap->init();

	_Owplayer = new Owplayer;
	_Owplayer->init();

	_villageMap->setOWPlayer(_Owplayer);
	_Owplayer->setScene(_villageMap);

	npcinit();

	return S_OK;
}

void villageScene::release(void)
{
	_villageMap->release();
	SAFE_DELETE(_villageMap);

	_Owplayer->release();
	SAFE_DELETE(_Owplayer);
}

void villageScene::update(void)
{
	camera();
	_villageMap->update();
	_Owplayer->update();
	npcUpdate();
}

void villageScene::render(void)
{
	_villageMap->render();
	_Owplayer->render();

	npcRender();

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
}

void villageScene::camera()
{
	switch (_villageMap->getState())
	{
	case VILLAGE:
	{

		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
				_npc[0].x += _Owplayer->getSpeed();

			}

			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}


		if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() < 800)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
				_npc[0].x -= _Owplayer->getSpeed();
			}

			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
				_npc[0].y += _Owplayer->getSpeed();
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}

		}

		if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 600)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
				_npc[0].y -= _Owplayer->getSpeed();
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
	}

	break;
	case HOUSE1:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case HOUSE2:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case STORE:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case SHOP:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case HOTEL1:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case HOTEL2:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case HOUSE3:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case HOUSE4:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	case DUNGEON:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}

			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() < 800)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}

			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}

		}

		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 600)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}

		break;
	case BOSSROOM:
		if (_Owplayer->getPlayerState() == MOVE_LEFT)
		{
			if (_Owplayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() - _Owplayer->getSpeed());
			}

			else
			{
				_Owplayer->setX(_Owplayer->getX() - _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_RIGHT)
		{
			if (_Owplayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
			{
				_villageMap->setBgX(_villageMap->getBgX() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setX(_Owplayer->getX() + _Owplayer->getSpeed());
			}
		}

		else if (_Owplayer->getPlayerState() == MOVE_UP)
		{
			if (_Owplayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			{
				_villageMap->setBgY(_villageMap->getBgY() - _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() - _Owplayer->getSpeed());
			}

		}
		else if (_Owplayer->getPlayerState() == MOVE_DOWN)
		{
			if (_Owplayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 398)
			{
				_villageMap->setBgY(_villageMap->getBgY() + _Owplayer->getSpeed());
			}
			else
			{
				_Owplayer->setY(_Owplayer->getY() + _Owplayer->getSpeed());
			}

		}
		break;
	default:
		break;
	}

}

void villageScene::npcinit()
{
	//¸¶À» NPC
	_npc[0].x = 739;
	_npc[0].y = 600;
	_npc[0].rc = RectMake(_npc[0].x, _npc[0].y, 50, 50);

	//house2 NPC
	_npc[1].ealryX = 278;
	_npc[1].ealryY = 371;
	_npc[1].x = 475;
	_npc[1].y = 371;
	_npc[1].endX = 555;
	_npc[1].endY = 371;
	_npc[1].rc = RectMake(_npc[1].x, _npc[1].y, 50, 50);
	_npc[1].isLeft = false;

	//house2 NPC
	_npc[2].x = _npc[1].x - 30;
	_npc[2].y = _npc[1].y;
	_npc[2].rc = RectMake(_npc[2].x, _npc[2].y, 50, 50);
	_npc[2].isLeft = false;

	//house3 NPC
	_npc[3].x = 400;
	_npc[3].y = 292;
	_npc[3].rc = RectMake(_npc[3].x, _npc[3].y, 50, 50);

	//shop NPC
	_npc[4].ealryX = 84;
	_npc[4].ealryY = 152;
	_npc[4].x = 84;
	_npc[4].y = 255;
	_npc[4].endX = 84;
	_npc[4].endY = 305;
	_npc[4].rc = RectMake(_npc[4].x, _npc[4].y, 50, 50);
	_npc[4].isDown = false;

}

void villageScene::npcUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		_npc[i].rc = RectMake(_npc[i].x, _npc[i].y, 50, 50);
	}

	if (_npc[1].rc.left < _npc[1].ealryX)
	{
		_npc[1].isLeft = true;
	}

	if (_npc[1].rc.right > _npc[1].endX)
	{
		_npc[1].isLeft = false;
	}

	if (_npc[1].isLeft == true)
	{
		_npc[1].x++;
	}

	if (_npc[1].isLeft == false)
	{
		_npc[1].x--;
	}

	_npc[2].x = _npc[1].x - 20;
	_npc[2].y = _npc[1].y;


	if (_npc[4].rc.top < _npc[4].ealryY)
	{
		_npc[4].isDown = true;
	}

	if (_npc[4].rc.bottom > _npc[4].endY)
	{
		_npc[4].isDown = false;
	}

	if (_npc[4].isDown == true)
	{
		_npc[4].y++;
	}

	if (_npc[4].isDown == false)
	{
		_npc[4].y--;
	}

}

void villageScene::npcRender()
{
	if (_villageMap->getState() == VILLAGE)
	{
		RectangleMake(getMemDC(), _npc[0].rc);
	}
	if (_villageMap->getState() == HOUSE2)
	{
		RectangleMake(getMemDC(), _npc[1].rc);
		RectangleMake(getMemDC(), _npc[2].rc);
	}
	if (_villageMap->getState() == HOUSE3)
	{
		RectangleMake(getMemDC(), _npc[3].rc);
	}
	if (_villageMap->getState() == SHOP)
	{
		RectangleMake(getMemDC(), _npc[4].rc);
	}
}
