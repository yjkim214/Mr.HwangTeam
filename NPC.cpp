#include "stdafx.h"
#include "NPC.h"
#include "villageMap.h"
#include "Owplayer.h"

HRESULT NPC::init(void)
{
	npcInit();
	_chat = new chat;
	_chat->init();

	frameCount = 0;
	_chatCount = 0;
	_chatEnd = false;
	return S_OK;
}

void NPC::release(void)
{
	_chat->release();
	SAFE_DELETE(_chat);
}

void NPC::update(void)
{
	frameCount++;
	camera();
	npcUpdate();
	col();
	_chat->update();
	NPCchat();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_chatCount++;
		SOUNDMANAGER->play("NPCchatMusic");
	}
}

void NPC::render(void)
{
	npcRender();
	//check();
}

void NPC::check()
{
	char str[256];
	sprintf(str, "%d", _npc[0].isChat);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void NPC::setRefer(villageMap * villageMap, Owplayer * owPlayer)
{
	_villageMap = villageMap;
	_owPlayer = owPlayer;
}

void NPC::camera()
{
	switch (_villageMap->getState())
	{
	case VILLAGE:
	{
		if (_villageMap->getIsMenu() == false)
		{
			if (_npc[0].isChat == false)
			{
				if (_owPlayer->getPlayerState() == MOVE_LEFT)
				{
					if (_owPlayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
					{
						_villageMap->setBgX(_villageMap->getBgX() - _owPlayer->getSpeed());
						_npc[0].x += _owPlayer->getSpeed();

					}

					else
					{
						_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
					}
				}


				if (_owPlayer->getPlayerState() == MOVE_RIGHT)
				{
					if (_owPlayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() < 800)
					{
						_villageMap->setBgX(_villageMap->getBgX() + _owPlayer->getSpeed());
						_npc[0].x -= _owPlayer->getSpeed();
					}

					else
					{
						_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
					}
				}

				if (_owPlayer->getPlayerState() == MOVE_UP)
				{
					if (_owPlayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
					{
						_villageMap->setBgY(_villageMap->getBgY() - _owPlayer->getSpeed());
						_npc[0].y += _owPlayer->getSpeed();
					}
					else
					{
						_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
					}

				}

				if (_owPlayer->getPlayerState() == MOVE_DOWN)
				{
					if (_owPlayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 600)
					{
						_villageMap->setBgY(_villageMap->getBgY() + _owPlayer->getSpeed());
						_npc[0].y -= _owPlayer->getSpeed();
					}
					else
					{
						_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());
					}

				}
			}
		}
	}

	break;
	case HOUSE1:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 750;
			_npc[0].y = 600;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());
			}
		}
		break;
	case HOUSE2:
		if (_villageMap->getIsMenu() == false)
		{
			if (_npc[1].isChat == false)
			{
				_npc[0].x = 751;
				_npc[0].y = 425;
				if (_owPlayer->getPlayerState() == MOVE_LEFT)
				{
					_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
				{
					_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_UP)
				{
					_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_DOWN)
				{
					_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

				}
			}
		}
		break;
	case STORE:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 751;
			_npc[0].y = 484;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

			}
		}
		break;
	case SHOP:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 751;
			_npc[0].y = 10;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

			}
		}
		break;
	case HOTEL1:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 36;
			_npc[0].y = 605;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

			}
		}
		break;
	case HOTEL2:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 36;
			_npc[0].y = 605;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

			}
		}
		break;
	case HOUSE3:
		if (_villageMap->getIsMenu() == false)
		{
			if (_npc[3].isChat == false)
			{
				_npc[0].x = -49;
				_npc[0].y = 310;
				if (_owPlayer->getPlayerState() == MOVE_LEFT)
				{
					_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
				{
					_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_UP)
				{
					_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
				}

				else if (_owPlayer->getPlayerState() == MOVE_DOWN)
				{
					_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());

				}
			}
		}
		break;
	case HOUSE4:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 151;
			_npc[0].y = -8;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			}

			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());
			}
		}
		break;
	case DUNGEON:
		if (_villageMap->getIsMenu() == false)
		{
			//_npc[0].x = 551;
			//_npc[0].y = -5;
			//if (_owPlayer->getPlayerState() == MOVE_LEFT)
			//{
			//	if (_owPlayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
			//	{
			//		_villageMap->setBgX(_villageMap->getBgX() - _owPlayer->getSpeed());
			//	}
			//
			//	else
			//	{
			//		_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
			//	}
			//}
			//
			//
			//else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			//{
			//	if (_owPlayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() < 800)
			//	{
			//		_villageMap->setBgX(_villageMap->getBgX() + _owPlayer->getSpeed());
			//	}
			//
			//	else
			//	{
			//		_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
			//	}
			//}
			//
			//else if (_owPlayer->getPlayerState() == MOVE_UP)
			//{
			//	if (_owPlayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
			//	{
			//		_villageMap->setBgY(_villageMap->getBgY() - _owPlayer->getSpeed());
			//	}
			//	else
			//	{
			//		_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
			//	}
			//
			//}
			//
			//else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			//{
			//	if (_owPlayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 600)
			//	{
			//		_villageMap->setBgY(_villageMap->getBgY() + _owPlayer->getSpeed());
			//	}
			//	else
			//	{
			//		_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());
			//	}
			//
			//}
		}
		break;
	case BOSSROOM:
		if (_villageMap->getIsMenu() == false)
		{
			_npc[0].x = 531;
			_npc[0].y = 601;
			if (_owPlayer->getPlayerState() == MOVE_LEFT)
			{
				if (_owPlayer->getCamera().left <= 0 && _villageMap->getBgX() > 0)
				{
					_villageMap->setBgX(_villageMap->getBgX() - _owPlayer->getSpeed());
				}

				else
				{
					_owPlayer->setX(_owPlayer->getX() - _owPlayer->getSpeed());
				}
			}

			else if (_owPlayer->getPlayerState() == MOVE_RIGHT)
			{
				if (_owPlayer->getCamera().right >= WINSIZEX && _villageMap->getBgX() <= 0)
				{
					_villageMap->setBgX(_villageMap->getBgX() + _owPlayer->getSpeed());
				}
				else
				{
					_owPlayer->setX(_owPlayer->getX() + _owPlayer->getSpeed());
				}
			}

			else if (_owPlayer->getPlayerState() == MOVE_UP)
			{
				if (_owPlayer->getCamera().top <= 0 && _villageMap->getBgY() > 0)
				{
					_villageMap->setBgY(_villageMap->getBgY() - _owPlayer->getSpeed());
				}
				else
				{
					_owPlayer->setY(_owPlayer->getY() - _owPlayer->getSpeed());
				}

			}
			else if (_owPlayer->getPlayerState() == MOVE_DOWN)
			{
				if (_owPlayer->getCamera().bottom >= WINSIZEY && _villageMap->getBgY() <= 398)
				{
					_villageMap->setBgY(_villageMap->getBgY() + _owPlayer->getSpeed());
				}
				else
				{
					_owPlayer->setY(_owPlayer->getY() + _owPlayer->getSpeed());
				}

			}
		}
		break;
	default:
		break;
	}

}

void NPC::npcInit()
{
	//마을 NPC
	_npc[0].x = 750;
	_npc[0].y = 600;
	_npc[0].rc = RectMake(_npc[0].x, _npc[0].y + 55, 45, 30);
	_npc[0].frameX = 0;
	_npc[0].frameY = 0;
	_npc[0].crashRc = RectMake(_npc[0].x, _npc[0].y, 30, 20);
	_npc[0].isChat = false;

	//house2 NPC
	_npc[1].ealryX = 278;
	_npc[1].ealryY = 371;
	_npc[1].x = 475;
	_npc[1].y = 371;
	_npc[1].endX = 555;
	_npc[1].endY = 371;
	_npc[1].rc = RectMake(_npc[1].x, _npc[1].y, 50, 50);
	_npc[1].frameX = 0;
	_npc[1].frameY = 0;
	_npc[1].isLeft = false;
	_npc[1].isChat = false;
	_npc[1].State = MOVE;
	_npc[1].crashRc = RectMake(_npc[1].x, _npc[1].y, 90, 50);

	//house2 NPC
	_npc[2].x = _npc[1].x + 35;
	_npc[2].y = _npc[1].y;
	_npc[2].rc = RectMake(_npc[2].x, _npc[2].y, 50, 50);
	_npc[2].frameX = 0;
	_npc[2].frameY = 0;
	_npc[2].isLeft = false;
	_npc[2].State = MOVE;

	//house3 NPC
	_npc[3].x = 400;
	_npc[3].y = 292;
	_npc[3].rc = RectMake(_npc[3].x, _npc[3].y, 25, 50);
	_npc[3].frameX = 0;
	_npc[3].frameY = 0;
	_npc[3].crashRc = RectMake(_npc[3].x, _npc[3].y, 50, 50);
	_npc[3].isChat = false;

	//shop NPC
	_npc[4].ealryX = 84;
	_npc[4].ealryY = 152;
	_npc[4].x = 84;
	_npc[4].y = 255;
	_npc[4].endX = 84;
	_npc[4].endY = 305;
	_npc[4].rc = RectMake(_npc[4].x, _npc[4].y, 50, 50);
	_npc[4].crashRc = RectMake(_npc[4].x, _npc[4].y, 130, 50);
	_npc[4].frameX = 0;
	_npc[4].frameY = 0;
	_npc[4].isDown = false;
	_npc[4].State = MOVE;
}

void NPC::npcUpdate()
{
	_npc[0].rc = RectMake(_npc[0].x, _npc[0].y + 60, 45, 30);
	_npc[0].crashRc = RectMake(_npc[0].x, _npc[0].y + 40, 60, 50);
	_npc[1].rc = RectMake(_npc[1].x, _npc[1].y, 50, 50);
	_npc[1].crashRc = RectMake(_npc[1].x, _npc[1].y, 90, 50);
	_npc[2].rc = RectMake(_npc[2].x, _npc[2].y, 30, 50);
	_npc[3].rc = RectMake(_npc[3].x, _npc[3].y, 25, 50);
	_npc[3].crashRc = RectMake(_npc[3].x, _npc[3].y, 50, 50);
	_npc[4].rc = RectMake(_npc[4].x, _npc[4].y, 50, 50);
	_npc[4].crashRc = RectMake(_npc[4].x, _npc[4].y, 130, 50);
	if (_npc[1].State == MOVE)
	{
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
	}
	_npc[2].x = _npc[1].x + 35;
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

void NPC::npcRender()
{

	if (_villageMap->getState() == VILLAGE)
	{

		//RectangleMake(getMemDC(), _npc[0].rc);
		if (KEYMANAGER->isToggleKey('S'))
		{
			RectangleMake(getMemDC(), _npc[0].crashRc);
		}
		IMAGEMANAGER->frameRender("NPCW", getMemDC(), _npc[0].x, _npc[0].y, _npc[0].frameX, _npc[0].frameY);
		if (frameCount % 8 == 0)
		{
			_npc[0].frameX++;
			if (_npc[0].frameX > 4)
			{
				_npc[0].frameX = 0;
			}
		}
	}
	if (_villageMap->getState() == HOUSE2)
	{
		//RectangleMake(getMemDC(), _npc[1].rc);
		//RectangleMake(getMemDC(), _npc[2].rc);
		if (KEYMANAGER->isToggleKey('S'))
		{
			RectangleMake(getMemDC(), _npc[1].crashRc);
		}
		IMAGEMANAGER->frameRender("NPCkid", getMemDC(), _npc[1].x, _npc[1].y, _npc[1].frameX, _npc[1].frameY);
		IMAGEMANAGER->frameRender("NPCkidW", getMemDC(), _npc[2].x, _npc[2].y, _npc[2].frameX, _npc[2].frameY);
		if (frameCount % 2 == 0)
		{
			if (_npc[1].isLeft == true)
			{
				_npc[1].frameX--;
				_npc[2].frameX--;
				_npc[1].frameY = 1;
				_npc[2].frameY = 1;
				if (_npc[1].frameX < 0 && _npc[2].frameX < 0)
				{
					_npc[1].frameX = 6;
					_npc[2].frameX = 6;
				}
			}
			if (_npc[1].isLeft == false)
			{
				_npc[1].frameX++;
				_npc[2].frameX++;
				_npc[1].frameY = 0;
				_npc[2].frameY = 0;
				if (_npc[1].frameX > 6 && _npc[2].frameX > 6)
				{
					_npc[1].frameX = 0;
					_npc[2].frameX = 0;
				}
			}
		}
	}
	if (_villageMap->getState() == HOUSE3)
	{
		if (KEYMANAGER->isToggleKey('S'))
		{
			RectangleMake(getMemDC(), _npc[3].crashRc);
		}
		IMAGEMANAGER->frameRender("NPC book", getMemDC(), _npc[3].x, _npc[3].y, _npc[3].frameX, _npc[3].frameY);
		if (frameCount % 8 == 0)
		{
			_npc[3].frameX++;
			if (_npc[3].frameX > 4)
			{
				_npc[3].frameX = 0;
			}
		}
	}
	if (_villageMap->getState() == SHOP)
	{
		//RectangleMake(getMemDC(), _npc[4].rc);
		if (KEYMANAGER->isToggleKey('S'))
		{
			RectangleMake(getMemDC(), _npc[4].crashRc);
		}
		if (_npc[4].isDown == true)
		{
			IMAGEMANAGER->frameRender("SHOP(NPC)", getMemDC(), _npc[4].x, _npc[4].y - 15, _npc[4].frameX, _npc[4].frameY);
		}
		if (_npc[4].isDown == false)
		{
			IMAGEMANAGER->frameRender("SHOP(NPC)back", getMemDC(), _npc[4].x, _npc[4].y - 15, _npc[4].frameX, _npc[4].frameY);
		}
		if (frameCount % 8 == 0)
		{
			_npc[4].frameX++;
			if (_npc[4].frameX > 5)
			{
				_npc[4].frameX = 0;
			}
		}
	}

	if (frameCount > 200)
	{
		frameCount = 0;
	}

}

void NPC::col()
{
	if (_villageMap->getState() == VILLAGE)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &_npc[0].rc, brush);
		DeleteObject(brush);

		COLORREF colorL = GetPixel(getMemDC(), _owPlayer->getProveLeft(),
			_owPlayer->getY() + 50);
		int rL = GetRValue(colorL);
		int gL = GetGValue(colorL);
		int bL = GetBValue(colorL);

		if (rL == 255 && gL == 0 && bL == 0)
		{
			_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
		}

		COLORREF colorR = GetPixel(getMemDC(), _owPlayer->getProveRight() + 5,
			_owPlayer->getY() + 50);
		int rR = GetRValue(colorR);
		int gR = GetGValue(colorR);
		int bR = GetBValue(colorR);

		if (rR == 255 && gR == 0 && bR == 0)
		{
			_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
		}

		COLORREF colorU = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveUp());
		int rU = GetRValue(colorU);
		int gU = GetGValue(colorU);
		int bU = GetBValue(colorU);

		if (rU == 255 && gU == 0 && bU == 0)
		{
			_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
		}

		COLORREF colorD = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveDown() + 10);
		int rD = GetRValue(colorD);
		int gD = GetGValue(colorD);
		int bD = GetBValue(colorD);

		if (rD == 255 && gD == 0 && bD == 0)
		{
			_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 12);
		}
	}

	if (_villageMap->getState() == HOUSE2)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &_npc[1].rc, brush);
		FillRect(getMemDC(), &_npc[2].rc, brush);
		DeleteObject(brush);

		COLORREF colorL = GetPixel(getMemDC(), _owPlayer->getProveLeft(),
			_owPlayer->getY() + 50);
		int rL = GetRValue(colorL);
		int gL = GetGValue(colorL);
		int bL = GetBValue(colorL);

		if (rL == 255 && gL == 0 && bL == 0)
		{
			_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
			_npc[1].isLeft = false;
		}

		COLORREF colorR = GetPixel(getMemDC(), _owPlayer->getProveRight() + 5,
			_owPlayer->getY() + 50);
		int rR = GetRValue(colorR);
		int gR = GetGValue(colorR);
		int bR = GetBValue(colorR);

		if (rR == 255 && gR == 0 && bR == 0)
		{
			_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 12);
			_npc[1].isLeft = true;
		}

		COLORREF colorU = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveUp());
		int rU = GetRValue(colorU);
		int gU = GetGValue(colorU);
		int bU = GetBValue(colorU);

		if (rU == 255 && gU == 0 && bU == 0)
		{
			_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
		}

		COLORREF colorD = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveDown() + 10);
		int rD = GetRValue(colorD);
		int gD = GetGValue(colorD);
		int bD = GetBValue(colorD);

		if (rD == 255 && gD == 0 && bD == 0)
		{
			_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 12);
		}
	}

	if (_villageMap->getState() == HOUSE3)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &_npc[3].rc, brush);
		DeleteObject(brush);

		COLORREF colorL = GetPixel(getMemDC(), _owPlayer->getProveLeft(),
			_owPlayer->getY() + 50);
		int rL = GetRValue(colorL);
		int gL = GetGValue(colorL);
		int bL = GetBValue(colorL);

		if (rL == 255 && gL == 0 && bL == 0)
		{
			_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
		}

		COLORREF colorR = GetPixel(getMemDC(), _owPlayer->getProveRight() + 5,
			_owPlayer->getY() + 50);
		int rR = GetRValue(colorR);
		int gR = GetGValue(colorR);
		int bR = GetBValue(colorR);

		if (rR == 255 && gR == 0 && bR == 0)
		{
			_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 12);
		}

		COLORREF colorU = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveUp());
		int rU = GetRValue(colorU);
		int gU = GetGValue(colorU);
		int bU = GetBValue(colorU);

		if (rU == 255 && gU == 0 && bU == 0)
		{
			_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
		}

		COLORREF colorD = GetPixel(getMemDC(), _owPlayer->getX() + 15,
			_owPlayer->getProveDown() + 10);
		int rD = GetRValue(colorD);
		int gD = GetGValue(colorD);
		int bD = GetBValue(colorD);

		if (rD == 255 && gD == 0 && bD == 0)
		{
			_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 12);
		}
	}
}

void NPC::NPCchat()
{
	RECT temp;
	//마을NPC 충돌 대화
	if (_villageMap->getState() == VILLAGE)
	{
		if (IntersectRect(&temp, &_owPlayer->getPlayerImg()->boundingBoxWithFrame(),
			&_npc[0].crashRc))
		{
			if (_chatCount == 1)
			{
				_npc[0].isChat = true;
			}
		}
		if (_npc[0].isChat == true)
		{
			_owPlayer->setPlayerState(IDLE);
			_chat->setCount(_chat->getCount() + 1);
		}
		if (_chatCount == 2)
		{
			if (_chat->getCount() <= 260)
			{
				_chat->setCount(260);
				_chatCount = 1;
			}
			else if (_chat->getCount() >= 260)
			{
				_chatCount = 3;
			}
		}
		else if (_chatCount == 3 && _chatEnd == false)
		{
			_npc[0].isChat = false;
			_chatCount = 0;
			_chat->setCount(0);
		}
	}

	//하우스2 충돌 대화
	if (_villageMap->getState() == HOUSE2)
	{
		if (IntersectRect(&temp, &_owPlayer->getPlayerImg()->boundingBoxWithFrame(),
			&_npc[1].crashRc))
		{
			if (_chatCount == 1)
			{
				_npc[1].State = STOP;
				_npc[1].isChat = true;

			}
		}

		if (_npc[1].isChat == true)
		{
			_owPlayer->setPlayerState(IDLE);
			_chat->setCount(_chat->getCount() + 1);
		}
		if (_chatCount == 2)
		{
			if (_chat->getCount() <= 120)
			{
				_chat->setCount(120);
				_chatCount = 1;
			}
			else if (_chat->getCount() >= 120)
			{
				_chatCount = 3;
			}
		}
		else if (_chatCount == 3 && _chatEnd == false)
		{
			_npc[1].isChat = false;
			_chatCount = 0;
			_chat->setCount(0);
			_npc[1].State = MOVE;
		}
	}
	//HOUSE3 아저씨 대화
	if (_villageMap->getState() == HOUSE3)
	{
		if (IntersectRect(&temp, &_owPlayer->getPlayerImg()->boundingBoxWithFrame(),
			&_npc[3].crashRc))
		{
			if (_chatCount == 1)
			{
				_npc[3].isChat = true;

			}
		}

		if (_npc[3].isChat == true)
		{
			_owPlayer->setPlayerState(IDLE);
			_chat->setCount(_chat->getCount() + 1);
		}
		if (_chatCount == 2)
		{
			_npc[3].isChat = false;
			_chatCount = 0;
			_chat->setCount(0);
		}
	}
}

void NPC::chatRender()
{
	if (_npc[0].isChat == true)
	{
		_chat->render();
		_chat->AlthenaChat();
	}
	if (_npc[1].isChat == true)
	{
		_chat->render();
		_chat->kidsChat();
	}
	if (_npc[3].isChat == true)
	{
		_chat->render();
		_chat->misterChat();
	}
}