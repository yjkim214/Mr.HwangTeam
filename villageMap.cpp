#include "stdafx.h"
#include "villageMap.h"
#include "Owplayer.h"

HRESULT villageMap::init(void)
{
	_state = VILLAGE;
	_bgX = 0;
	_bgY = 0;
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
		break;
	case HOUSE1:
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
		IMAGEMANAGER->render("village", getMemDC(), _bgX, _bgY);
	}
	break;
	case HOUSE1:
	{
		IMAGEMANAGER->render("house1", getMemDC(), 0, 0);
	}
	break;
	case HOUSE2:
	{
		IMAGEMANAGER->render("house2", getMemDC(), 0, 0);
	}
	break;
	case STORE:
	{
		IMAGEMANAGER->render("strore", getMemDC(), 0, 0);
	}
	break;
	case SHOP:
	{
		IMAGEMANAGER->render("shop", getMemDC(), 0, 0);
	}
	break;
	case HOTEL1:
	{
		IMAGEMANAGER->render("hotel1", getMemDC(), 0, 0);
	}
	break;
	case HOTEL2:
	{
		IMAGEMANAGER->render("hotel2", getMemDC(), 0, 0);
	}
	break;
	case HOUSE3:
	{
		IMAGEMANAGER->render("house3", getMemDC(), 0, 0);
	}
	break;
	case HOUSE4:
	{
		IMAGEMANAGER->render("house4", getMemDC(), 0, 0);
	}
	break;
	case DUNGEON:
	{

	}
	break;
	case BOSSROOM:
	{
		IMAGEMANAGER->loopRender("BossRoomSky", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loofX, 0);
		IMAGEMANAGER->render("BossRoom", getMemDC(), 0, _bgY);
	}
	break;
	default:
		break;
	}

	//char str[256];
	//sprintf(str, "bgX : %d", _bgX);
	//HFONT myfont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­");
	//SelectObject(getMemDC(), myfont);
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	//TextOut(getMemDC(), 10, 100, str, strlen(str));
	//check();
	//DeleteObject(myfont);
}

void villageMap::check()
{
	char str[256];
	sprintf(str, "ptMouseX : %d, ptMouseY : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

