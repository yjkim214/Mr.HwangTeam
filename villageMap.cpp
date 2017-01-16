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
	_pixelHouse2 = IMAGEMANAGER->findImage("house2Pixel");
	_pixelStroe = IMAGEMANAGER->findImage("strorePixel");
	_pixelShop = IMAGEMANAGER->findImage("shopPixel");
	_pixelHotel1 = IMAGEMANAGER->findImage("hotel1Pixel");
	_pixelHotel2 = IMAGEMANAGER->findImage("hotel2Pixel");
	_pixelHouse3 = IMAGEMANAGER->findImage("house3Pixel");
	_pixelHouse4 = IMAGEMANAGER->findImage("house4Pixel");
	_pixelDungeon = IMAGEMANAGER->findImage("dungeonPixel");
	_pixelBoss = IMAGEMANAGER->findImage("BossRoomPixel");

	is1Floor = false;
	isDungeon = false;
	isBoss = false;
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
		house1PixelCol();
	}
	break;
	case HOUSE2:
	{
		house2PixelCol();
	}
	break;
	case STORE:
	{
		storePixelCol();
	}
	break;
	case SHOP:
	{
		shopPixelCol();
	}
	break;
	case HOTEL1:
	{
		hotel1PixelCol();
	}
	break;
	case HOTEL2:
	{
		hotel2PixelCol();
	}
	break;
	case HOUSE3:
	{
		house3PixelCol();
	}
	break;
	case HOUSE4:
	{
		house4PixelCol();
	}
	break;
	//case DUNGEON:
	//{
	//	dungeonPixelCol();
	//}
	break;
	case BOSSROOM:
	{
		_loofX++;
		bossRoomPixelCol();
	}
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
		IMAGEMANAGER->render("village", getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelVillage->render(getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
		}
	}
	break;
	case HOUSE1:
	{
		IMAGEMANAGER->render("house1", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHouse1->render(getMemDC());
		}
	}
	break;
	case HOUSE2:
	{
		IMAGEMANAGER->render("house2", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHouse2->render(getMemDC());
		}
	}
	break;
	case STORE:
	{
		IMAGEMANAGER->render("strore", getMemDC());
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelStroe->render(getMemDC());
		}
	}
	break;
	case SHOP:
	{
		IMAGEMANAGER->render("shop", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelShop->render(getMemDC());
		}
	}
	break;
	case HOTEL1:
	{
		IMAGEMANAGER->render("hotel1", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHotel1->render(getMemDC());
		}
	}
	break;
	case HOTEL2:
	{
		IMAGEMANAGER->render("hotel2", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHotel2->render(getMemDC());
		}
	}
	break;
	case HOUSE3:
	{
		IMAGEMANAGER->render("house3", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHouse3->render(getMemDC());
		}
	}
	break;
	case HOUSE4:
	{
		IMAGEMANAGER->render("house4", getMemDC(), 0, 0, 0, 0, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelHouse4->render(getMemDC());
		}
	}
	break;
	//case DUNGEON:
	//{
	//	IMAGEMANAGER->render("dungeon", getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
	//	if (KEYMANAGER->isToggleKey('A'))
	//	{
	//		_pixelDungeon->render(getMemDC(), 0, 0, _bgX, _bgY, 1600 - _bgX, 1200 - _bgY);
	//	}
	//}
	//break;
	case BOSSROOM:
	{
		IMAGEMANAGER->loopRender("BossRoomSky", getMemDC(), &RectMake(0, 0, 800, 1600), _loofX, 0);
		IMAGEMANAGER->render("BossRoom", getMemDC(), 0, 0, 0, _bgY, 800, 600);
		if (KEYMANAGER->isToggleKey('A'))
		{
			_pixelBoss->render(getMemDC(), 0, 0, 0, _bgY, 800, 600);
		}
	}
	break;
	default:
		break;
	}



	//char str[256];
	//sprintf(str, "bgX : %d", _bgX);
	//TextOut(getMemDC(), 10, 200, str, strlen(str));
	//sprintf(str, "bgY : %d", _bgY);
	////HFONT myfont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서");
	////SelectObject(getMemDC(), myfont);
	////SetTextColor(getMemDC(), RGB(0, 0, 0));
	//TextOut(getMemDC(), 10, 250, str, strlen(str));
	////check();
	////DeleteObject(myfont);

}

void villageMap::check()
{
	char str[256];
	sprintf(str, "ptMouseX : %d, ptMouseY : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 10, 10, str, strlen(str));


}

void villageMap::villagePixelCol()
{

	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelVillage->getMemDC(), _bgX + _owPlayer->getProveLeft()
		, (_owPlayer->getY() + 50) + _bgY);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 22);
	}


	//오른쪽검사
	for (int i = _owPlayer->getProveRight(); i < _owPlayer->getProveRight() + 10; i++)
	{
		COLORREF colorR = GetPixel(_pixelVillage->getMemDC(), i + _bgX,
			(_owPlayer->getY() + 50) + _bgY);
		int rR = GetRValue(colorR);
		int gR = GetGValue(colorR);
		int bR = GetBValue(colorR);
		if (rR == 255 && gR == 0 && bR == 0)
		{
			_owPlayer->setX(i - _owPlayer->getPlayerImg()->getFrameWidth() + 4);
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
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 255 && g == 255 && b == 255)
		{
			_state = STORE;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(470);
			_owPlayer->setY(510);
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 0 && g == 255 && b == 0)
		{
			_state = SHOP;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(150);
			_owPlayer->setY(480);
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 0 && g == 0 && b == 100)
		{
			_state = HOTEL1;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(340);
			_owPlayer->setY(490);
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 200 && g == 200 && b == 200)
		{
			_state = HOUSE3;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(260);
			_owPlayer->setY(500);
			_bgX = 0;
			_bgY = 0;
			break;
		}
		if (r == 100 && g == 100 && b == 100)
		{
			_state = HOUSE4;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(220);
			_owPlayer->setY(470);
			_bgX = 0;
			_bgY = 0;
			break;
		}

		if (r == 0 && g == 0 && b == 255)
		{
			_state = BOSSROOM;
			_owPlayer->setLookat(UP);
			_owPlayer->setX(380);
			_owPlayer->setY(530);
			_bgX = 0;
			_bgY = 400;
		}
	}

	//if (isDungeon == true)
	//{
	//	_owPlayer->setLookat(UP);
	//	isDungeon = false;
	//}

	if (isBoss == true)
	{
		_owPlayer->setY(63);
		isBoss = false;
	}
}

void villageMap::house1PixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHouse1->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHouse1->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelHouse1->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 0;
		_bgY = 0;
		_owPlayer->setX(315);
		_owPlayer->setY(195);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHouse1->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}


}

void villageMap::house2PixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHouse2->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHouse2->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelHouse2->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 0;
		_bgY = 174;
		_owPlayer->setX(207);
		_owPlayer->setY(429);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHouse2->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}

}

void villageMap::storePixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelStroe->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelStroe->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelStroe->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 0;
		_bgY = 118;
		_owPlayer->setX(386);
		_owPlayer->setY(403);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelStroe->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}
}

void villageMap::shopPixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelShop->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelShop->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelShop->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 0;
		_bgY = 590;
		_owPlayer->setX(280);
		_owPlayer->setY(403);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelShop->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}
}

void villageMap::hotel1PixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHotel1->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHotel1->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	if (rR == 0 && gR == 255 & bR == 0)
	{
		_state = HOTEL2;
		_owPlayer->setLookat(RIGHT);
		_owPlayer->setX(110);
		_owPlayer->setY(503);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelHotel1->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 716;
		_bgY = 0;
		_owPlayer->setX(550);
		_owPlayer->setY(285);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHotel1->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}
	if (is1Floor == true)
	{
		_owPlayer->setX(660);
		_owPlayer->setY(443);
		is1Floor = false;
	}
}

void villageMap::hotel2PixelCol()
{

	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHotel2->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}
	if (rL == 0 && gL == 0 && bL == 255)
	{
		is1Floor = true;
		_state = HOTEL1;
		_owPlayer->setLookat(LEFT);
	}

	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHotel2->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}


	//위 검사
	COLORREF colorU = GetPixel(_pixelHotel2->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHotel2->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}

}

void villageMap::house3PixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHouse3->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHouse3->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelHouse3->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 802;
		_bgY = 290;
		_owPlayer->setX(570);
		_owPlayer->setY(357);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHouse3->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}
}

void villageMap::house4PixelCol()
{
	//왼쪽검사

	COLORREF colorL = GetPixel(_pixelHouse4->getMemDC(), _owPlayer->getProveLeft(), _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);
	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}


	//오른쪽검사
	COLORREF colorR = GetPixel(_pixelHouse4->getMemDC(), _owPlayer->getProveRight() + 5, _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	//위 검사
	COLORREF colorU = GetPixel(_pixelHouse4->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}
	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_owPlayer->setLookat(DOWN);
		_bgX = 602;
		_bgY = 608;
		_owPlayer->setX(551);
		_owPlayer->setY(403);
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelHouse4->getMemDC(), _owPlayer->getX() + 15, _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}

}

void villageMap::dungeonPixelCol()
{
	COLORREF colorL = GetPixel(_pixelDungeon->getMemDC(), _bgX + _owPlayer->getProveLeft(), _bgY + _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);

	if (rL == 255 && gL == 0 && bL == 0 || rL == 0 && gL == 255 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}

	if (rL == 0 && gL == 0 && bL == 255)
	{
		_state = VILLAGE;
		_bgX = 201;
		_bgY = 603;
		_owPlayer->setX(539);
		_owPlayer->setY(443);
		isDungeon = true;
	}

	COLORREF colorR = GetPixel(_pixelDungeon->getMemDC(), _bgX + _owPlayer->getProveRight() + 5, _bgY + _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0 || rR == 0 && gR == 255 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	COLORREF colorU = GetPixel(_pixelDungeon->getMemDC(), _bgX + _owPlayer->getX() + 15, _bgY + _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0 || rU == 0 && gU == 255 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}


	//아래 검사
	COLORREF colorD = GetPixel(_pixelDungeon->getMemDC(), _bgX + _owPlayer->getX() + 15, _bgY + _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0 || rD == 0 && gD == 255 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}

}

void villageMap::bossRoomPixelCol()
{
	//왼검사
	COLORREF colorL = GetPixel(_pixelBoss->getMemDC(), _owPlayer->getProveLeft(), _bgY + _owPlayer->getY() + 50);
	int rL = GetRValue(colorL);
	int gL = GetGValue(colorL);
	int bL = GetBValue(colorL);

	if (rL == 255 && gL == 0 && bL == 0)
	{
		_owPlayer->setX(_owPlayer->getProveLeft() + _owPlayer->getPlayerImg()->getFrameWidth() - 20);
	}



	COLORREF colorR = GetPixel(_pixelBoss->getMemDC(), _owPlayer->getProveRight() + 5, _bgY + _owPlayer->getY() + 50);
	int rR = GetRValue(colorR);
	int gR = GetGValue(colorR);
	int bR = GetBValue(colorR);
	if (rR == 255 && gR == 0 && bR == 0)
	{
		_owPlayer->setX(_owPlayer->getProveRight() - _owPlayer->getPlayerImg()->getFrameWidth() + 13);
	}

	COLORREF colorU = GetPixel(_pixelBoss->getMemDC(), _owPlayer->getX() + 15, _bgY + _owPlayer->getProveUp());
	int rU = GetRValue(colorU);
	int gU = GetGValue(colorU);
	int bU = GetBValue(colorU);
	if (rU == 255 && gU == 0 && bU == 0)
	{
		_owPlayer->setY(_owPlayer->getProveUp() + _owPlayer->getPlayerImg()->getFrameHeight() - 87);
	}

	if (rU == 0 && gU == 0 && bU == 255)
	{
		_state = VILLAGE;
		_bgX = 219;
		_bgY = 0;
		_owPlayer->setLookat(DOWN);
		_owPlayer->setX(530);

		isBoss = true;
	}

	//아래 검사
	COLORREF colorD = GetPixel(_pixelBoss->getMemDC(), _owPlayer->getX() + 15, _bgY + _owPlayer->getProveDown() + 10);
	int rD = GetRValue(colorD);
	int gD = GetGValue(colorD);
	int bD = GetBValue(colorD);
	if (rD == 255 && gD == 0 && bD == 0)
	{
		_owPlayer->setY(_owPlayer->getProveDown() - _owPlayer->getPlayerImg()->getFrameHeight() + 13);
	}


}

