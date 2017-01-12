#include "stdafx.h"
#include "Owplayer.h"
#include "villageMap.h"

HRESULT Owplayer::init(void)
{
	_playerImg = IMAGEMANAGER->findImage("owPlayer_idle");
	_inven = IMAGEMANAGER->findImage("inven");
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_att = 5.0f;
	_dex = 3.0f;
	_speed = 2.5f;
	_state = IDLE;
	_lookat = DOWN;
	_animcount = 0;
	_invenRect = RectMakeCenter(WINSIZEX / 2 + 50, WINSIZEY - 25, 50, 50);


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

	_invenRect = RectMakeCenter(WINSIZEX / 2 + 50, WINSIZEY - 25, 50, 50);

	if ((PtInRect(&_invenRect, _ptMouse)) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isinven = true;
	}
	ProveUpdate();
}

void Owplayer::render(void)
{

	_playerImg->frameRender(getMemDC(), _x, _y);

	Rectangle(getMemDC(), _invenRect.left, _invenRect.top, _invenRect.right, _invenRect.bottom);


	if (KEYMANAGER->isToggleKey('0'))
	{
		Rectangle(getMemDC(), _camera.left, _camera.top, _camera.right, _camera.bottom);

	}


	if (_Scene->getState() == VILLAGE)
	{
		IMAGEMANAGER->alphaRender("village_building", getMemDC(), 0, 0, _Scene->getBgX(), _Scene->getBgY(),
			1600 - _Scene->getBgX(), 1200 - _Scene->getBgY(), 100);
		IMAGEMANAGER->alphaRender("village_in", getMemDC(), 0, 0, _Scene->getBgX(), _Scene->getBgY(),
			1600 - _Scene->getBgX(), 1200 - _Scene->getBgY(), 100);
	}

	if (_Scene->getState() == DUNGEON)
	{
		IMAGEMANAGER->alphaRender("dungeon_tree", getMemDC(), 0, 0, _Scene->getBgX(), _Scene->getBgY(),
			1600 - _Scene->getBgX(), 1200 - _Scene->getBgY(), 100);
	}

	if (_isinven == true)
	{
		_inven->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
	}

	Rectangle(getMemDC(), _proveLeft, _y, _proveLeft + 10, _y + 10);
	Rectangle(getMemDC(), _proveRight, _y, _proveRight + 10, _y + 10);
	Rectangle(getMemDC(), _x, _proveUp, _x + 10, _proveUp + 10);
	Rectangle(getMemDC(), _x, _proveDown, _x + 10, _proveDown + 10);
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
			if (_camera.left <= 0 && _Scene->getBgX() >= 0)
			{
				_Scene->setBgX(_Scene->getBgX() - _speed / 2);
				if (_Scene->getState() != VILLAGE &&_Scene->getState() != DUNGEON &&
					_Scene->getState() != BOSSROOM)
				{
					_Scene->setBgX(0);
					_x -= _speed;
				}
			}

			else
			{
				_x -= _speed;
			}

			_lookat = LEFT;
		}
	}

	if (_state == MOVE_RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_camera.right >= WINSIZEX && _Scene->getBgX() <= 800)
			{
				_Scene->setBgX(_Scene->getBgX() + _speed);
				if (_Scene->getState() != VILLAGE &&_Scene->getState() != DUNGEON &&
					_Scene->getState() != BOSSROOM)
				{
					_Scene->setBgX(0);
					_x += _speed;
				}
			}

			else
			{
				_x += _speed;
			}

			_lookat = RIGHT;
		}
	}

	if (_state == MOVE_UP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_camera.top <= 0 && _Scene->getBgY() >= 0)
			{
				_Scene->setBgY(_Scene->getBgY() - _speed / 2);
				if (_Scene->getState() != VILLAGE &&_Scene->getState() != DUNGEON &&
					_Scene->getState() != BOSSROOM)
				{
					_Scene->setBgY(0);
					_y -= _speed;
				}
			}

			else
			{
				_y -= _speed;
			}

			_lookat = UP;
		}
	}

	if (_state == MOVE_DOWN)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{

			if (_camera.bottom >= WINSIZEY && _Scene->getBgY() <= 600)
			{
				_Scene->setBgY(_Scene->getBgY() + _speed);
				if (_Scene->getState() != VILLAGE &&_Scene->getState() != DUNGEON &&
					_Scene->getState() != BOSSROOM)
				{
					_Scene->setBgY(0);
					_y += _speed;
				}
			}

			else
			{
				_y += _speed;
			}

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

void Owplayer::inventory()
{



}

void Owplayer::ProveUpdate()
{
	_proveLeft = _x - _playerImg->getFrameWidth() / 15;
	_proveRight = _x + _playerImg->getFrameWidth() - 15;
	_proveUp = _y + _playerImg->getFrameHeight() - 40;
	_proveDown = _y + _playerImg->getFrameHeight() - 15;
}
