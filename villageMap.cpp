#include "stdafx.h"
#include "villageMap.h"
#include "Owplayer.h"

HRESULT villageMap::init(void)
{
	_state = VILLAGE;
	_bgX = 0;
	_bgY = 0;
	_pixelVillage = IMAGEMANAGER->findImage("villagePixel");
	_pixelHouse1 = IMAGEMANAGER->findImage("house1Pixel");
	return S_OK;
}

void villageMap::release(void)
{
}

void villageMap::update(void)
{

	switch (_state)
	{
	case VILLAGE:
	{
		villagePixelCol();
	}
	break;
	case HOUSE1:
	{
		//house1PixelCol();
	}
	break;
	case HOUSE2:
		break;
	case STORE:
		break;
	case SHOP:
		break;
	case HOTEL1:
		break;
	case HOTEL2:
		break;
	case HOUSE3:
		break;
	case HOUSE4:
		break;
	case DUNGEON:
		break;
	case BOSSROOM:
		_loofX++;
		break;
	default:
		break;
	}

}

void villageMap::render(void)
{
	switch (_state)
	{
	case VILLAGE:
	{
		_pixelVillage->render(getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
		IMAGEMANAGER->render("village", getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
	}
	break;
	case HOUSE1:
	{
		IMAGEMANAGER->render("house1", getMemDC(), 0, 0, 0, 0, 800, 600);
		_pixelHouse1->render(getMemDC());
	}
	break;
	case HOUSE2:
	{
		IMAGEMANAGER->render("house2", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case STORE:
	{
		IMAGEMANAGER->render("strore", getMemDC(), 150, 150, 0, 0, 500, 458);
	}
	break;
	case SHOP:
	{
		IMAGEMANAGER->render("shop", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case HOTEL1:
	{
		IMAGEMANAGER->render("hotel1", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case HOTEL2:
	{
		IMAGEMANAGER->render("hotel2", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case HOUSE3:
	{
		IMAGEMANAGER->render("house3", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case HOUSE4:
	{
		IMAGEMANAGER->render("house4", getMemDC(), 0, 0, 0, 0, 800, 600);
	}
	break;
	case DUNGEON:
	{
		IMAGEMANAGER->render("dungeon", getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
	}
	break;
	case BOSSROOM:
	{
		IMAGEMANAGER->loopRender("BossRoomSky", getMemDC(), &RectMake(0, 0, 800, 1600), _loofX, 0);
		IMAGEMANAGER->render("BossRoom", getMemDC(), 0, 0, 0, _bgY, 800, 600);
	}
	break;
	default:
		break;
	}



	char str[256];
	sprintf(str, "bgX : %d", _bgX);
	TextOut(getMemDC(), 10, 200, str, strlen(str));
	sprintf(str, "bgY : %d", _bgY);
	//HFONT myfont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서");
	//SelectObject(getMemDC(), myfont);
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), 10, 250, str, strlen(str));
	//check();
	//DeleteObject(myfont);

}

void villageMap::check()
{
	//char str[256];
	//sprintf(str, "ptMouseX : %d, ptMouseY : %d", _ptMouse.x, _ptMouse.y);
	//TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void villageMap::villagePixelCol()
{

	//왼쪽검사
	for (int i = _owPlayer->getProveLeft(); i < _owPlayer->getProveLeft() + 8; i++)
	{
		COLORREF color = GetPixel(_pixelVillage->getMemDC(), 10 + i + _bgX, (_owPlayer->getY() + 50) + _bgY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			_owPlayer->setX(i + 5);
			break;
		}
	}

	//오른쪽검사
	for (int i = _owPlayer->getProveRight(); i < _owPlayer->getProveRight() + 8; i++)
	{
		COLORREF color = GetPixel(_pixelVillage->getMemDC(), i + _bgX, (_owPlayer->getY() + 50) + _bgY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			_owPlayer->setX(i - 20);
			break;
		}
	}

	//위쪽검사
	for (int i = _owPlayer->getProveUp(); i < _owPlayer->getProveUp() + 8; i++)
	{
		COLORREF color = GetPixel(_pixelVillage->getMemDC(), (_owPlayer->getX() + 15) + _bgX, i + _bgY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			_owPlayer->setY(i + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
			break;
		}
		if (r == 255 && g == 255 && b == 0)
		{
			_state = DUNGEON;
			_owPlayer->setLookat(RIGHT);
			_owPlayer->setX(40);
			_owPlayer->setY(70);
			_bgX = 0;
			_bgY = 0;
			break;
		}
	}

	//아래 검사
	for (int i = _owPlayer->getProveDown(); i < _owPlayer->getProveDown() + 8; i++)
	{
		COLORREF color = GetPixel(_pixelVillage->getMemDC(), (_owPlayer->getX() + 15) + _bgX, i + _bgY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			_owPlayer->setY(i - _owPlayer->getPlayerImg()->getFrameHeight() + 6);
			break;
		}
		if (r == 255 && g == 0 && b == 255)
		{
			_state = HOUSE1;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(390);
			_owPlayer->setY(510);
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 0 && g == 255 && b == 255)
		{
			_state = HOUSE2;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(400);
			_owPlayer->setY(510);
			break;
		}
		if (r == 255 && g == 255 && b == 255)
		{
			_state = STORE;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(470);
			_owPlayer->setY(510);
			break;
		}
		if (r == 0 && g == 255 && b == 0)
		{
			_state = SHOP;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(150);
			_owPlayer->setY(480);
			break;
		}
		if (r == 0 && g == 0 && b == 100)
		{
			_state = HOTEL1;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(340);
			_owPlayer->setY(490);
			break;
		}
		if (r == 200 && g == 200 && b == 200)
		{
			_state = HOUSE3;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(260);
			_owPlayer->setY(500);
			break;
		}
		if (r == 100 && g == 100 && b == 100)
		{
			_state = HOUSE4;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(220);
			_owPlayer->setY(470);
			break;
		}

		if (r == 0 && g == 0 && b == 255)
		{
			_state = BOSSROOM;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(380);
			_owPlayer->setY(530);
			_bgY = 400;
			break;
		}
	}

}

void villageMap::house1PixelCol()
{

}

void villageMap::house2PixelCol()
{
}

void villageMap::storePixelCol()
{
}

void villageMap::shopPixelCol()
{
}

void villageMap::hotel1PixelCol()
{
}

void villageMap::hotel2PixelCol()
{
}

void villageMap::house3PixelCol()
{
}

void villageMap::house4PixelCol()
{
}

void villageMap::dungeonPixelCol()
{
}

void villageMap::bossRoomPixelCol()
{
}

