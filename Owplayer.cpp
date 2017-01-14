#include "stdafx.h"
#include "Owplayer.h"
#include "villageMap.h"
//#include "inventory.h"

HRESULT Owplayer::init(void)
{
	//_inventory = new inventory;
	//_inventory->init();

	_playerImg = IMAGEMANAGER->findImage("owPlayer_idle");

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_att = 5.0f;
	_dex = 3.0f;
	_speed = 3;
	_state = IDLE;
	_lookat = DOWN;
	_animcount = 0;


	_proveLeft = _x - _playerImg->getFrameWidth() / 4;
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



	ProveUpdate();
	//_inventory->update();
}

void Owplayer::render(void)
{
	_playerImg->frameRender(getMemDC(), _x, _y);




	if (KEYMANAGER->isToggleKey('0'))
	{
		Rectangle(getMemDC(), _camera.left, _camera.top, _camera.right, _camera.bottom);
	}

	//_inventory->render();

	if (KEYMANAGER->isToggleKey('1'))
	{
		Rectangle(getMemDC(), _proveLeft, _y, _proveLeft + 10, _y + 10);
		Rectangle(getMemDC(), _proveRight, _y, _proveRight + 10, _y + 10);
		Rectangle(getMemDC(), _x, _proveUp, _x + 10, _proveUp + 10);
		Rectangle(getMemDC(), _x, _proveDown, _x + 10, _proveDown + 10);
	}
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
	_proveLeft = _x - _playerImg->getFrameWidth() / 4;
	_proveRight = _x + _playerImg->getFrameWidth() - 15;
	_proveUp = _y + _playerImg->getFrameHeight() - 40;
	_proveDown = _y + _playerImg->getFrameHeight() - 15;
}
