#include "stdafx.h"
#include "owDungeon.h"

HRESULT owDungeon::init(void)
{
	//============================================================================================
	//															공통변수 초기화
	//============================================================================================
	_time = 0;
	_monsterNumber = 0;
	_backX = PLAYERDATA->getBackX();
	_backY = PLAYERDATA->getBackY();

	_probeX01 = _monster.x - _monster.w / 2;
	_probeX02 = _monster.x + _monster.w / 2;
	_probeY01 = _monster.y - _monster.h / 2;
	_probeY02 = _monster.y + _monster.h / 2;

	_probeX11 = _slime.x - _slime.w / 2;
	_probeX12 = _slime.x + _slime.w / 2;
	_probeY11 = _slime.y - _slime.h / 2;
	_probeY12 = _slime.y + _slime.h / 2;

	_probeX21 = _fluffyBug.x - _fluffyBug.w / 2;
	_probeX22 = _fluffyBug.x + _fluffyBug.w / 2;
	_probeY21 = _fluffyBug.y - _fluffyBug.h / 2;
	_probeY22 = _fluffyBug.y + _fluffyBug.h / 2;

	_probeX31 = _flytrapper.x - _flytrapper.w / 2;
	_probeX32 = _flytrapper.x + _flytrapper.w / 2;
	_probeY31 = _flytrapper.y - _flytrapper.h / 2;
	_probeY32 = _flytrapper.y + _flytrapper.h / 2;

	_probeX41 = _barbarian.x - _barbarian.w / 2;
	_probeX42 = _barbarian.x + _barbarian.w / 2;
	_probeY41 = _barbarian.y - _barbarian.h / 2;
	_probeY42 = _barbarian.y + _barbarian.h / 2;

	_probeX51 = _devilBomber.x - _devilBomber.w / 2;
	_probeX52 = _devilBomber.x + _devilBomber.w / 2;
	_probeY51 = _devilBomber.y - _devilBomber.h / 2;
	_probeY52 = _devilBomber.y + _devilBomber.h / 2;

	isUpCollision0 = false;
	isDownCollision0 = false;
	isLeftCollision0 = false;
	isRightCollision0 = false;

	isUpCollision1 = false;
	isDownCollision1 = false;
	isLeftCollision1 = false;
	isRightCollision1 = false;

	isUpCollision2 = false;
	isDownCollision2 = false;
	isLeftCollision2 = false;
	isRightCollision2 = false;

	isUpCollision3 = false;
	isDownCollision3 = false;
	isLeftCollision3 = false;
	isRightCollision3 = false;

	isUpCollision4 = false;
	isDownCollision4 = false;
	isLeftCollision4 = false;
	isRightCollision4 = false;

	isUpCollision5 = false;
	isDownCollision5 = false;
	isLeftCollision5 = false;
	isRightCollision5 = false;

	//============================================================================================
	//															플레이어 초기화
	//============================================================================================
	_monster.x = PLAYERDATA->getMonsterX();
	_monster.y = PLAYERDATA->getMonsterY();
	_monster.angle = 0;
	_monster.currentFrameX = 0;
	_monster.moveSpeed = 3.0f;
	_monster.w = 30;
	_monster.h = 65;
	_monster.rc = RectMakeCenter(_monster.x, _monster.y, _monster.w, _monster.h);
	_monster.isLeft = false;
	_monster.isRight = false;
	_monster.isUp = false;
	_monster.isDown = false;

	//============================================================================================
	//															몬스터 초기화
	//============================================================================================
	_slime.x = PLAYERDATA->getSlimeX();
	_slime.y = PLAYERDATA->getSlimeY();
	_slime.angle = 0;
	_slime.moveSpeed = 1.0f;
	_slime.w = 60;
	_slime.h = 60;
	_slime.currentFrameX = 0;
	_slime.currentFrameY = 0;
	_slime.rc = RectMakeCenter(_slime.x, _slime.y, _slime.w, _slime.h);
	_slime.rcExplore = RectMakeCenter(_slime.x, _slime.y, 300, 300);
	_slime.isDie = false;

	_fluffyBug.x = PLAYERDATA->getFluffyBugX();
	_fluffyBug.y = PLAYERDATA->getFluffyBugY();
	_fluffyBug.angle = 0;
	_fluffyBug.moveSpeed = 1.0f;
	_fluffyBug.w = 40;
	_fluffyBug.h = 48;
	_fluffyBug.currentFrameX = 0;
	_fluffyBug.currentFrameY = 0;
	_fluffyBug.rc = RectMakeCenter(_fluffyBug.x, _fluffyBug.y, _fluffyBug.w, _fluffyBug.h);
	_fluffyBug.rcExplore = RectMakeCenter(_fluffyBug.x, _fluffyBug.y, 300, 300);
	_fluffyBug.isDie = false;

	_flytrapper.x = PLAYERDATA->getFlytrapperX();
	_flytrapper.y = PLAYERDATA->getFlytrapperY();
	_flytrapper.angle = 0;
	_flytrapper.moveSpeed = 1.0f;
	_flytrapper.w = 85;
	_flytrapper.h = 83;
	_flytrapper.currentFrameX = 0;
	_flytrapper.currentFrameY = 0;
	_flytrapper.rc = RectMakeCenter(_flytrapper.x, _flytrapper.y, _flytrapper.w, _flytrapper.h);
	_flytrapper.rcExplore = RectMakeCenter(_flytrapper.x, _flytrapper.y, 300, 300);
	_flytrapper.isDie = false;

	_barbarian.x = PLAYERDATA->getBarbarianX();
	_barbarian.y = PLAYERDATA->getBarbarianY();
	_barbarian.angle = 0;
	_barbarian.moveSpeed = 1.0f;
	_barbarian.w = 54;
	_barbarian.h = 69;
	_barbarian.currentFrameX = 0;
	_barbarian.currentFrameY = 0;
	_barbarian.rc = RectMakeCenter(_barbarian.x, _barbarian.y, _barbarian.w, _barbarian.h);
	_barbarian.rcExplore = RectMakeCenter(_barbarian.x, _barbarian.y, 300, 300);
	_barbarian.isDie = false;

	_devilBomber.x = PLAYERDATA->getDevilBomberX();
	_devilBomber.y = PLAYERDATA->getDevilBomberY();
	_devilBomber.angle = 0;
	_devilBomber.moveSpeed = 1.0f;
	_devilBomber.w = 74;
	_devilBomber.h = 68;
	_devilBomber.currentFrameX = 0;
	_devilBomber.currentFrameY = 0;
	_devilBomber.rc = RectMakeCenter(_devilBomber.x, _devilBomber.y, _devilBomber.w, _devilBomber.h);
	_devilBomber.rcExplore = RectMakeCenter(_devilBomber.x, _devilBomber.y, 300, 300);
	_devilBomber.isDie = false;

	return S_OK;
}

void owDungeon::release(void)
{
}

void owDungeon::update(void)
{
	_time++;

	_probeX01 = _monster.x - _monster.w / 2;
	_probeX02 = _monster.x + _monster.w / 2;
	_probeY01 = _monster.y - _monster.h / 2;
	_probeY02 = _monster.y + _monster.h / 2;

	_probeX11 = _slime.x - _slime.w / 2;
	_probeX12 = _slime.x + _slime.w / 2;
	_probeY11 = _slime.y - _slime.h / 2;
	_probeY12 = _slime.y + _slime.h / 2;

	_probeX21 = _fluffyBug.x - _fluffyBug.w / 2;
	_probeX22 = _fluffyBug.x + _fluffyBug.w / 2;
	_probeY21 = _fluffyBug.y - _fluffyBug.h / 2;
	_probeY22 = _fluffyBug.y + _fluffyBug.h / 2;

	_probeX31 = _flytrapper.x - _flytrapper.w / 2;
	_probeX32 = _flytrapper.x + _flytrapper.w / 2;
	_probeY31 = _flytrapper.y - _flytrapper.h / 2;
	_probeY32 = _flytrapper.y + _flytrapper.h / 2;

	_probeX41 = _barbarian.x - _barbarian.w / 2;
	_probeX42 = _barbarian.x + _barbarian.w / 2;
	_probeY41 = _barbarian.y - _barbarian.h / 2;
	_probeY42 = _barbarian.y + _barbarian.h / 2;

	_probeX51 = _devilBomber.x - _devilBomber.w / 2;
	_probeX52 = _devilBomber.x + _devilBomber.w / 2;
	_probeY51 = _devilBomber.y - _devilBomber.h / 2;
	_probeY52 = _devilBomber.y + _devilBomber.h / 2;


	if (_backX > 800)
	{
		_backX = 800;
	}

	if (_backX <= 0)
	{
		_backX = 0;
	}

	if (_time < 10)
	{
		PLAYERDATA->setMonsterNumber(0);
	}

	//==========================================픽셀 충돌============================================
	//==========================================플레이어==============================================
	for (int i = _probeY01 + 5; i < _probeY01 + 15; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _monster.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision0 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_monster.y = i + _monster.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_monster.y = i + _monster.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY02 - 5; i < _probeY02 + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _monster.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision0 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_monster.y = i - _monster.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_monster.y = i - _monster.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX01 + 5; i < _probeX01 + 15; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _monster.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision0 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_monster.x = i + _monster.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_monster.x = i + _monster.w / 2;
				break;
			}
			if ((r == 0 && g == 0 && b == 255))
			{
				SCENEMANAGER->changeScene("마을");
				break;
			}
		}
	}

	for (int i = _probeX02 - 5; i < _probeX02 + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _monster.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision0 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_monster.x = i - _monster.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_monster.x = i - _monster.w / 2;
				break;
			}
		}
	}
	//==========================================슬라임==============================================
	for (int i = _probeY11 + 5; i < _probeY11 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _slime.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision1 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_slime.y = i + _slime.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_slime.y = i + _slime.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY12 - 10; i < _probeY12 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _slime.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision1 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_slime.y = i - _slime.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_slime.y = i - _slime.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX11 + 5; i < _probeX11 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _slime.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision1 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_slime.x = i + _slime.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_slime.x = i + _slime.w / 2;
				break;
			}
		}
	}

	for (int i = _probeX12 - 10; i < _probeX12 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _slime.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision1 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_slime.x = i - _slime.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_slime.x = i - _slime.w / 2;
				break;
			}
		}
	}
	//==========================================플러피버그==============================================
	for (int i = _probeY21 + 5; i < _probeY21 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _fluffyBug.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision2 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_fluffyBug.y = i + _fluffyBug.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_fluffyBug.y = i + _fluffyBug.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY22 - 10; i < _probeY22 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _fluffyBug.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision2 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_fluffyBug.y = i - _fluffyBug.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_fluffyBug.y = i - _fluffyBug.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX21 + 5; i < _probeX21 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _fluffyBug.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision2 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_fluffyBug.x = i + _fluffyBug.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_fluffyBug.x = i + _fluffyBug.w / 2;
				break;
			}
		}
	}

	for (int i = _probeX22 - 10; i < _probeX22 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _fluffyBug.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision2 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_fluffyBug.x = i - _fluffyBug.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_fluffyBug.x = i - _fluffyBug.w / 2;
				break;
			}
		}
	}
	//==========================================플라이트렙퍼==============================================
	for (int i = _probeY31 + 5; i < _probeY31 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _flytrapper.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision3 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_flytrapper.y = i + _flytrapper.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_flytrapper.y = i + _flytrapper.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY32 - 10; i < _probeY32 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _flytrapper.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision3 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_flytrapper.y = i - _flytrapper.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_flytrapper.y = i - _flytrapper.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX31 + 5; i < _probeX31 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _flytrapper.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision3 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_flytrapper.x = i + _flytrapper.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_flytrapper.x = i + _flytrapper.w / 2;
				break;
			}
		}
	}

	for (int i = _probeX32 - 10; i < _probeX32 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _flytrapper.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision3 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_flytrapper.x = i - _flytrapper.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_flytrapper.x = i - _flytrapper.w / 2;
				break;
			}
		}
	}
	//==========================================바바리안==============================================
	for (int i = _probeY41 + 5; i < _probeY41 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _barbarian.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision4 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_barbarian.y = i + _barbarian.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_barbarian.y = i + _barbarian.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY42 - 10; i < _probeY42 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _barbarian.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision4 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_barbarian.y = i - _barbarian.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_barbarian.y = i - _barbarian.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX41 + 5; i < _probeX41 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _barbarian.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision4 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_barbarian.x = i + _barbarian.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_barbarian.x = i + _barbarian.w / 2;
				break;
			}
		}
	}

	for (int i = _probeX42 - 10; i < _probeX42 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _barbarian.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision4 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_barbarian.x = i - _barbarian.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_barbarian.x = i - _barbarian.w / 2;
				break;
			}
		}
	}
	//==========================================데블붐버==============================================
	for (int i = _probeY51 + 5; i < _probeY51 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _devilBomber.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isUpCollision5 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_devilBomber.y = i + _devilBomber.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_devilBomber.y = i + _devilBomber.h / 2;
				break;
			}
		}
	}

	for (int i = _probeY52 - 10; i < _probeY52 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), _devilBomber.x + _backX, i + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isDownCollision5 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_devilBomber.y = i - _devilBomber.h / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_devilBomber.y = i - _devilBomber.h / 2;
				break;
			}
		}
	}

	for (int i = _probeX51 + 5; i < _probeX51 + 25; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _devilBomber.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isLeftCollision5 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_devilBomber.x = i + _devilBomber.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_devilBomber.x = i + _devilBomber.w / 2;
				break;
			}
		}
	}

	for (int i = _probeX52 - 10; i < _probeX52 + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("dungeonPixel")->getMemDC(), i + _backX, _devilBomber.y + _backY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (isRightCollision5 == false)
		{
			if ((r == 255 && g == 0 && b == 0))
			{
				_devilBomber.x = i - _devilBomber.w / 2;
				break;
			}
			if ((r == 0 && g == 255 && b == 0))
			{
				_devilBomber.x = i - _devilBomber.w / 2;
				break;
			}
		}
	}


	//============================================================================================
	//															플레이어 이동
	//============================================================================================
	if (_monster.x < _slime.x)
	{
		isRightCollision1 = true;
	}
	if (_monster.x > _slime.x)
	{
		isLeftCollision1 = true;
	}
	if (_monster.y < _slime.y)
	{
		isDownCollision1 = true;
	}
	if (_monster.y > _slime.y)
	{
		isUpCollision1 = true;
	}

	if (_monster.x < _fluffyBug.x)
	{
		isRightCollision2 = true;
	}
	if (_monster.x > _fluffyBug.x)
	{
		isLeftCollision2 = true;
	}
	if (_monster.y < _fluffyBug.y)
	{
		isDownCollision2 = true;
	}
	if (_monster.y > _fluffyBug.y)
	{
		isUpCollision2 = true;
	}

	if (_monster.x < _flytrapper.x)
	{
		isRightCollision3 = true;
	}
	if (_monster.x > _flytrapper.x)
	{
		isLeftCollision3 = true;
	}
	if (_monster.y < _flytrapper.y)
	{
		isDownCollision3 = true;
	}
	if (_monster.y > _flytrapper.y)
	{
		isUpCollision3 = true;
	}

	if (_monster.x < _barbarian.x)
	{
		isRightCollision4 = true;
	}
	if (_monster.x > _barbarian.x)
	{
		isLeftCollision4 = true;
	}
	if (_monster.y < _barbarian.y)
	{
		isDownCollision4 = true;
	}
	if (_monster.y > _barbarian.y)
	{
		isUpCollision4 = true;
	}

	if (_monster.x < _devilBomber.x)
	{
		isRightCollision5 = true;
	}
	if (_monster.x > _devilBomber.x)
	{
		isLeftCollision5 = true;
	}
	if (_monster.y < _devilBomber.y)
	{
		isDownCollision5 = true;
	}
	if (_monster.y > _devilBomber.y)
	{
		isUpCollision5 = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_monster.isLeft = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_monster.isRight = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_monster.isUp = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_monster.isDown = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_monster.isLeft = false;
		_monster.isRight = false;
		_monster.isUp = false;
		_monster.isDown = false;

		isLeftCollision0 = false;
		isRightCollision0 = true;

		isLeftCollision1 = false;
		isLeftCollision2 = false;
		isLeftCollision3 = false;
		isLeftCollision4 = false;
		isLeftCollision5 = false;
		if (_monster.x >= 400)
		{
			_monster.x -= _monster.moveSpeed;
		}
		if (_monster.x < 400 && _backX <= 800 && _backX > 0)
		{
			_backX -= _monster.moveSpeed;
			_slime.x += _monster.moveSpeed;
			_fluffyBug.x += _monster.moveSpeed;
			_flytrapper.x += _monster.moveSpeed;
			_barbarian.x += _monster.moveSpeed;
			_devilBomber.x += _monster.moveSpeed;
		}
		if (_monster.x < 400 && _backX == 0)
		{
			_monster.x -= _monster.moveSpeed;
		}
		PLAYERDATA->setMonsterX(_monster.x);
		PLAYERDATA->setMonsterY(_monster.y);
		PLAYERDATA->setBackX(_backX);
		PLAYERDATA->setBackY(_backY);
		PLAYERDATA->setSlimeX(_slime.x);
		PLAYERDATA->setSlimeY(_slime.y);
		PLAYERDATA->setFluffyBugX(_fluffyBug.x);
		PLAYERDATA->setFluffyBugY(_fluffyBug.y);
		PLAYERDATA->setFlytrapperX(_flytrapper.x);
		PLAYERDATA->setFlytrapperY(_flytrapper.y);
		PLAYERDATA->setBarbarianX(_barbarian.x);
		PLAYERDATA->setBarbarianY(_barbarian.y);
		PLAYERDATA->setDevilBomberX(_devilBomber.x);
		PLAYERDATA->setDevilBomberY(_devilBomber.y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_monster.isLeft = false;
		_monster.isRight = false;
		_monster.isUp = false;
		_monster.isDown = false;

		isRightCollision0 = false;
		isLeftCollision0 = true;

		isRightCollision1 = false;
		isRightCollision2 = false;
		isRightCollision3 = false;
		isRightCollision4 = false;
		isRightCollision5 = false;
		if (_monster.x < 400)
		{
			_monster.x += _monster.moveSpeed;
		}
		if (_monster.x >= 400 && _backX < 800)
		{
			_backX += _monster.moveSpeed;
			_slime.x -= _monster.moveSpeed;
			_fluffyBug.x -= _monster.moveSpeed;
			_flytrapper.x -= _monster.moveSpeed;
			_barbarian.x -= _monster.moveSpeed;
			_devilBomber.x -= _monster.moveSpeed;
		}
		if (_monster.x >= 400 && _backX >= 800)
		{
			_monster.x += _monster.moveSpeed;
		}
		PLAYERDATA->setMonsterX(_monster.x);
		PLAYERDATA->setMonsterY(_monster.y);
		PLAYERDATA->setBackX(_backX);
		PLAYERDATA->setBackY(_backY);
		PLAYERDATA->setSlimeX(_slime.x);
		PLAYERDATA->setSlimeY(_slime.y);
		PLAYERDATA->setFluffyBugX(_fluffyBug.x);
		PLAYERDATA->setFluffyBugY(_fluffyBug.y);
		PLAYERDATA->setFlytrapperX(_flytrapper.x);
		PLAYERDATA->setFlytrapperY(_flytrapper.y);
		PLAYERDATA->setBarbarianX(_barbarian.x);
		PLAYERDATA->setBarbarianY(_barbarian.y);
		PLAYERDATA->setDevilBomberX(_devilBomber.x);
		PLAYERDATA->setDevilBomberY(_devilBomber.y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_monster.isLeft = false;
		_monster.isRight = false;
		_monster.isUp = false;
		_monster.isDown = false;

		isUpCollision0 = false;
		isDownCollision0 = true;

		isUpCollision1 = false;
		isUpCollision2 = false;
		isUpCollision3 = false;
		isUpCollision4 = false;
		isUpCollision5 = false;
		if (_monster.y >= 300)
		{
			_monster.y -= _monster.moveSpeed;
		}
		if (_monster.y < 300 && _backY <= 600 && _backY > 0)
		{
			_backY -= _monster.moveSpeed;
			_slime.y += _monster.moveSpeed;
			_fluffyBug.y += _monster.moveSpeed;
			_flytrapper.y += _monster.moveSpeed;
			_barbarian.y += _monster.moveSpeed;
			_devilBomber.y += _monster.moveSpeed;
		}
		if (_monster.y < 300 && _backY == 0)
		{
			_monster.y -= _monster.moveSpeed;
		}
		PLAYERDATA->setMonsterX(_monster.x);
		PLAYERDATA->setMonsterY(_monster.y);
		PLAYERDATA->setBackX(_backX);
		PLAYERDATA->setBackY(_backY);
		PLAYERDATA->setSlimeX(_slime.x);
		PLAYERDATA->setSlimeY(_slime.y);
		PLAYERDATA->setFluffyBugX(_fluffyBug.x);
		PLAYERDATA->setFluffyBugY(_fluffyBug.y);
		PLAYERDATA->setFlytrapperX(_flytrapper.x);
		PLAYERDATA->setFlytrapperY(_flytrapper.y);
		PLAYERDATA->setBarbarianX(_barbarian.x);
		PLAYERDATA->setBarbarianY(_barbarian.y);
		PLAYERDATA->setDevilBomberX(_devilBomber.x);
		PLAYERDATA->setDevilBomberY(_devilBomber.y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_monster.isLeft = false;
		_monster.isRight = false;
		_monster.isUp = false;
		_monster.isDown = false;

		isDownCollision0 = false;
		isUpCollision0 = true;

		isDownCollision1 = false;
		isDownCollision2 = false;
		isDownCollision3 = false;
		isDownCollision4 = false;
		isDownCollision5 = false;
		if (_monster.y < 300)
		{
			_monster.y += _monster.moveSpeed;
		}
		if (_monster.y >= 300 && _backY < 600)
		{
			_backY += _monster.moveSpeed;
			_slime.y -= _monster.moveSpeed;
			_fluffyBug.y -= _monster.moveSpeed;
			_flytrapper.y -= _monster.moveSpeed;
			_barbarian.y -= _monster.moveSpeed;
			_devilBomber.y -= _monster.moveSpeed;
		}
		if (_monster.y >= 300 && _backY == 600)
		{
			_monster.y += _monster.moveSpeed;
		}
		PLAYERDATA->setMonsterX(_monster.x);
		PLAYERDATA->setMonsterY(_monster.y);
		PLAYERDATA->setBackX(_backX);
		PLAYERDATA->setBackY(_backY);
		PLAYERDATA->setSlimeX(_slime.x);
		PLAYERDATA->setSlimeY(_slime.y);
		PLAYERDATA->setFluffyBugX(_fluffyBug.x);
		PLAYERDATA->setFluffyBugY(_fluffyBug.y);
		PLAYERDATA->setFlytrapperX(_flytrapper.x);
		PLAYERDATA->setFlytrapperY(_flytrapper.y);
		PLAYERDATA->setBarbarianX(_barbarian.x);
		PLAYERDATA->setBarbarianY(_barbarian.y);
		PLAYERDATA->setDevilBomberX(_devilBomber.x);
		PLAYERDATA->setDevilBomberY(_devilBomber.y);
	}
	_monster.rc = RectMakeCenter(_monster.x, _monster.y, _monster.w, _monster.h);


	//============================================================================================
	//															몬스터 이동
	//============================================================================================
	RECT temp;
	_slime.isDie = PLAYERDATA->getSlimeDie();
	if (_slime.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_slime.rcExplore))
		{
			_slime.x -= cosf(getAngle(_monster.x, _monster.y, _slime.x, _slime.y)) * _slime.moveSpeed;
			_slime.y += sinf(getAngle(_monster.x, _monster.y, _slime.x, _slime.y)) * _slime.moveSpeed;
		}
		_slime.rc = RectMakeCenter(_slime.x, _slime.y, _slime.w, _slime.h);
		_slime.rcExplore = RectMakeCenter(_slime.x, _slime.y, 300, 300);
	}

	if (_fluffyBug.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_fluffyBug.rcExplore))
		{
			_fluffyBug.angle = getAngle(_monster.x, _monster.y, _fluffyBug.x, _fluffyBug.y);
			_fluffyBug.x -= cosf(_fluffyBug.angle) * _fluffyBug.moveSpeed;
			_fluffyBug.y += sinf(_fluffyBug.angle) * _fluffyBug.moveSpeed;
		}
		_fluffyBug.rc = RectMakeCenter(_fluffyBug.x, _fluffyBug.y, _fluffyBug.w, _fluffyBug.h);
		_fluffyBug.rcExplore = RectMakeCenter(_fluffyBug.x, _fluffyBug.y, 300, 300);
	}

	if (_flytrapper.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_flytrapper.rcExplore))
		{
			_flytrapper.angle = getAngle(_monster.x, _monster.y, _flytrapper.x, _flytrapper.y);
			_flytrapper.x -= cosf(_flytrapper.angle) * _flytrapper.moveSpeed;
			_flytrapper.y += sinf(_flytrapper.angle) * _flytrapper.moveSpeed;
		}
		_flytrapper.rc = RectMakeCenter(_flytrapper.x, _flytrapper.y, _flytrapper.w, _flytrapper.h);
		_flytrapper.rcExplore = RectMakeCenter(_flytrapper.x, _flytrapper.y, 300, 300);
	}

	if (_barbarian.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_barbarian.rcExplore))
		{
			_barbarian.angle = getAngle(_monster.x, _monster.y, _barbarian.x, _barbarian.y);
			_barbarian.x -= cosf(_barbarian.angle) * _barbarian.moveSpeed;
			_barbarian.y += sinf(_barbarian.angle) * _barbarian.moveSpeed;
		}
		_barbarian.rc = RectMakeCenter(_barbarian.x, _barbarian.y, _barbarian.w, _barbarian.h);
		_barbarian.rcExplore = RectMakeCenter(_barbarian.x, _barbarian.y, 300, 300);
	}

	if (_devilBomber.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_devilBomber.rcExplore))
		{
			_devilBomber.angle = getAngle(_monster.x, _monster.y, _devilBomber.x, _devilBomber.y);
			_devilBomber.x -= cosf(_devilBomber.angle) * _devilBomber.moveSpeed;
			_devilBomber.y += sinf(_devilBomber.angle) * _devilBomber.moveSpeed;
		}
		_devilBomber.rc = RectMakeCenter(_devilBomber.x, _devilBomber.y, _devilBomber.w, _devilBomber.h);
		_devilBomber.rcExplore = RectMakeCenter(_devilBomber.x, _devilBomber.y, 300, 300);
	}

	//============================================================================================
	//															몬스터 프레임
	//============================================================================================
	if (_time % 10 == 0)
	{
		_monster.currentFrameX++;
		if (_monster.currentFrameX >= 4)
		{
			_monster.currentFrameX = 0;
		}

		_slime.currentFrameX++;
		if (_slime.currentFrameX >= 3)
		{
			_slime.currentFrameX = 0;
		}

		_fluffyBug.currentFrameX++;
		if (_fluffyBug.currentFrameX >= 3)
		{
			_fluffyBug.currentFrameX = 0;
		}

		_flytrapper.currentFrameX++;
		if (_flytrapper.currentFrameX >= 3)
		{
			_flytrapper.currentFrameX = 0;
		}

		_barbarian.currentFrameX++;
		if (_barbarian.currentFrameX >= 3)
		{
			_barbarian.currentFrameX = 0;
		}

		_devilBomber.currentFrameX++;
		if (_devilBomber.currentFrameX >= 4)
		{
			_devilBomber.currentFrameX = 0;
		}
	}


	//============================================================================================
	//															몬스터 충돌
	//============================================================================================

	if (_slime.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_slime.rc))
		{
			PLAYERDATA->setMonsterNumber(1);
			SCENEMANAGER->changeScene("배틀화면");
		}
	}

	if (_fluffyBug.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_fluffyBug.rc))
		{
			PLAYERDATA->setMonsterNumber(2);
			SCENEMANAGER->changeScene("배틀화면");
		}
	}

	if (_flytrapper.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_flytrapper.rc))
		{
			PLAYERDATA->setMonsterNumber(3);
			SCENEMANAGER->changeScene("배틀화면");
		}
	}

	if (_barbarian.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_barbarian.rc))
		{
			PLAYERDATA->setMonsterNumber(4);
			SCENEMANAGER->changeScene("배틀화면");
		}
	}

	if (_devilBomber.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_devilBomber.rc))
		{
			PLAYERDATA->setMonsterNumber(5);
			SCENEMANAGER->changeScene("배틀화면");
		}
	}
}

void owDungeon::render(void)
{
	IMAGEMANAGER->render("dungeon", getMemDC(), 0, 0, _backX, _backY, 800, 600);
	if (KEYMANAGER->isToggleKey('A'))
	{
		IMAGEMANAGER->render("dungeonPixel", getMemDC(), 0, 0, _backX, _backY, 800, 600);
	}
	

	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		RectangleMake(getMemDC(), _monster.rc);
		if (_slime.isDie == false)
		{
			RectangleMake(getMemDC(), _slime.rcExplore);
		}
		RectangleMake(getMemDC(), _fluffyBug.rcExplore);
		RectangleMake(getMemDC(), _flytrapper.rcExplore);
		RectangleMake(getMemDC(), _barbarian.rcExplore);
		RectangleMake(getMemDC(), _devilBomber.rcExplore);
	}

	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		if (_slime.isDie == false)
		{
			RectangleMake(getMemDC(), _slime.rc);
		}
		RectangleMake(getMemDC(), _fluffyBug.rc);
		RectangleMake(getMemDC(), _flytrapper.rc);
		RectangleMake(getMemDC(), _barbarian.rc);
		RectangleMake(getMemDC(), _devilBomber.rc);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		IMAGEMANAGER->frameRender("owPlayer_move", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, _monster.currentFrameX, 1);
	}
	if (_monster.isLeft == true)
	{
		IMAGEMANAGER->frameRender("owPlayer_idle", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, 1, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		IMAGEMANAGER->frameRender("owPlayer_move", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, _monster.currentFrameX, 3);
	}
	if (_monster.isRight == true)
	{
		IMAGEMANAGER->frameRender("owPlayer_idle", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, 3, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		IMAGEMANAGER->frameRender("owPlayer_move", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, _monster.currentFrameX, 0);
	}
	if (_monster.isUp == true)
	{
		IMAGEMANAGER->frameRender("owPlayer_idle", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		IMAGEMANAGER->frameRender("owPlayer_move", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, _monster.currentFrameX, 2);
	}
	if (_monster.isDown == true)
	{
		IMAGEMANAGER->frameRender("owPlayer_idle", getMemDC(), _monster.x - (_monster.w) / 2, _monster.y - (_monster.h) / 2, 2, 0);
	}

	IMAGEMANAGER->alphaRender("dungeon_tree", getMemDC(), 0, 0, _backX, _backY, 800, 600, 100);

	RECT temp;
	if (_slime.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_slime.rcExplore))
		{
			IMAGEMANAGER->frameRender("slime", getMemDC(), _slime.x - (_slime.w) / 2, _slime.y - (_slime.h) / 2, _slime.currentFrameX, 0);
		}
		else
		{
			IMAGEMANAGER->render("slime", getMemDC(), _slime.x - (_slime.w) / 2, _slime.y - (_slime.h) / 2, 0, 0, 60, 60);
		}
	}

	if (_fluffyBug.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_fluffyBug.rcExplore))
		{
			if (_fluffyBug.angle >= PI * 14 / 8 || _fluffyBug.angle < PI / 4)
			{
				IMAGEMANAGER->frameRender("fluffyBugLeft", getMemDC(), _fluffyBug.x - (_fluffyBug.w) / 2, _fluffyBug.y - (_fluffyBug.h) / 2, _fluffyBug.currentFrameX, 0);
			}
			if (_fluffyBug.angle >= PI / 4 && _fluffyBug.angle < PI * 3 / 4)
			{
				IMAGEMANAGER->frameRender("fluffyBugDown", getMemDC(), _fluffyBug.x - (_fluffyBug.w) / 2, _fluffyBug.y - (_fluffyBug.h) / 2, _fluffyBug.currentFrameX, 0);
			}
			if (_fluffyBug.angle >= PI * 3 / 4 && _fluffyBug.angle < PI * 5 / 4)
			{
				IMAGEMANAGER->frameRender("fluffyBugRight", getMemDC(), _fluffyBug.x - (_fluffyBug.w) / 2, _fluffyBug.y - (_fluffyBug.h) / 2, _fluffyBug.currentFrameX, 0);
			}
			if (_fluffyBug.angle >= PI * 5 / 4 && _fluffyBug.angle < PI * 7 / 4)
			{
				IMAGEMANAGER->frameRender("fluffyBugUp", getMemDC(), _fluffyBug.x - (_fluffyBug.w) / 2, _fluffyBug.y - (_fluffyBug.h) / 2, _fluffyBug.currentFrameX, 0);
			}
		}
		else
		{
			IMAGEMANAGER->render("fluffyBugDown", getMemDC(), _fluffyBug.x - (_fluffyBug.w) / 2, _fluffyBug.y - (_fluffyBug.h) / 2, 0, 0, 40, 48);
		}
	}

	if (_flytrapper.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_flytrapper.rcExplore))
		{
			if (_flytrapper.angle >= PI * 14 / 8 || _flytrapper.angle < PI / 4)
			{
				IMAGEMANAGER->frameRender("flytrapperLeft", getMemDC(), _flytrapper.x - (_flytrapper.w) / 2, _flytrapper.y - (_flytrapper.h) / 2, _flytrapper.currentFrameX, 0);
			}
			if (_flytrapper.angle >= PI / 4 && _flytrapper.angle < PI * 3 / 4)
			{
				IMAGEMANAGER->frameRender("flytrapperDown", getMemDC(), _flytrapper.x - (_flytrapper.w) / 2, _flytrapper.y - (_flytrapper.h) / 2, _flytrapper.currentFrameX, 0);
			}
			if (_flytrapper.angle >= PI * 3 / 4 && _flytrapper.angle < PI * 5 / 4)
			{
				IMAGEMANAGER->frameRender("flytrapperRight", getMemDC(), _flytrapper.x - (_flytrapper.w) / 2, _flytrapper.y - (_flytrapper.h) / 2, _flytrapper.currentFrameX, 0);
			}
			if (_flytrapper.angle >= PI * 5 / 4 && _flytrapper.angle < PI * 7 / 4)
			{
				IMAGEMANAGER->frameRender("flytrapperUp", getMemDC(), _flytrapper.x - (_flytrapper.w) / 2, _flytrapper.y - (_flytrapper.h) / 2, _flytrapper.currentFrameX, 0);
			}
		}
		else
		{
			IMAGEMANAGER->render("flytrapperDown", getMemDC(), _flytrapper.x - (_flytrapper.w) / 2, _flytrapper.y - (_flytrapper.h) / 2, 0, 0, 85, 83);
		}
	}

	if (_barbarian.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_barbarian.rcExplore))
		{
			if (_barbarian.angle >= PI * 14 / 8 || _barbarian.angle < PI / 4)
			{
				IMAGEMANAGER->frameRender("barbarianLeft", getMemDC(), _barbarian.x - (_barbarian.w) / 2, _barbarian.y - (_barbarian.h) / 2, _barbarian.currentFrameX, 0);
			}
			if (_barbarian.angle >= PI / 4 && _barbarian.angle < PI * 3 / 4)
			{
				IMAGEMANAGER->frameRender("barbarianDown", getMemDC(), _barbarian.x - (_barbarian.w) / 2, _barbarian.y - (_barbarian.h) / 2, _barbarian.currentFrameX, 0);
			}
			if (_barbarian.angle >= PI * 3 / 4 && _barbarian.angle < PI * 5 / 4)
			{
				IMAGEMANAGER->frameRender("barbarianRight", getMemDC(), _barbarian.x - (_barbarian.w) / 2, _barbarian.y - (_barbarian.h) / 2, _barbarian.currentFrameX, 0);
			}
			if (_barbarian.angle >= PI * 5 / 4 && _barbarian.angle < PI * 7 / 4)
			{
				IMAGEMANAGER->frameRender("barbarianUp", getMemDC(), _barbarian.x - (_barbarian.w) / 2, _barbarian.y - (_barbarian.h) / 2, _barbarian.currentFrameX, 0);
			}
		}
		else
		{
			IMAGEMANAGER->render("barbarianDown", getMemDC(), _barbarian.x - (_barbarian.w) / 2, _barbarian.y - (_barbarian.h) / 2, 0, 0, 54, 69);
		}
	}

	if (_devilBomber.isDie == false)
	{
		if (IntersectRect(&temp, &_monster.rc, &_devilBomber.rcExplore))
		{
			if (_devilBomber.angle >= PI * 14 / 8 || _devilBomber.angle < PI / 4)
			{
				IMAGEMANAGER->frameRender("devilBomberLeft", getMemDC(), _devilBomber.x - (_devilBomber.w) / 2, _devilBomber.y - (_devilBomber.h) / 2, _devilBomber.currentFrameX, 0);
			}
			if (_devilBomber.angle >= PI / 4 && _devilBomber.angle < PI * 3 / 4)
			{
				IMAGEMANAGER->frameRender("devilBomberDown", getMemDC(), _devilBomber.x - (_devilBomber.w) / 2, _devilBomber.y - (_devilBomber.h) / 2, _devilBomber.currentFrameX, 0);
			}
			if (_devilBomber.angle >= PI * 3 / 4 && _devilBomber.angle < PI * 5 / 4)
			{
				IMAGEMANAGER->frameRender("devilBomberRight", getMemDC(), _devilBomber.x - (_devilBomber.w) / 2, _devilBomber.y - (_devilBomber.h) / 2, _devilBomber.currentFrameX, 0);
			}
			if (_devilBomber.angle >= PI * 5 / 4 && _devilBomber.angle < PI * 7 / 4)
			{
				IMAGEMANAGER->frameRender("devilBomberUp", getMemDC(), _devilBomber.x - (_devilBomber.w) / 2, _devilBomber.y - (_devilBomber.h) / 2, _devilBomber.currentFrameX, 0);
			}
		}
		else
		{
			IMAGEMANAGER->render("devilBomberDown", getMemDC(), _devilBomber.x - (_devilBomber.w) / 2, _devilBomber.y - (_devilBomber.h) / 2, 0, 0, 74, 68);
		}
	}



	char str[32];
	sprintf(str, "%d, %d", int(_monster.x), int(_backX));
	TextOut(getMemDC(), 30, 50, str, strlen(str));

	sprintf(str, "%d, %d", int(_monster.y), int(_backY));
	TextOut(getMemDC(), 30, 70, str, strlen(str));

	if (KEYMANAGER->isToggleKey('A'))
	{
		RectangleMakeCenter(getMemDC(), _probeX01, _monster.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX02, _monster.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _monster.x, _probeY01, 20, 20);
		RectangleMakeCenter(getMemDC(), _monster.x, _probeY02, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX11, _slime.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX12, _slime.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _slime.x, _probeY11, 20, 20);
		RectangleMakeCenter(getMemDC(), _slime.x, _probeY12, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX21, _fluffyBug.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX22, _fluffyBug.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _fluffyBug.x, _probeY21, 20, 20);
		RectangleMakeCenter(getMemDC(), _fluffyBug.x, _probeY22, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX31, _flytrapper.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX32, _flytrapper.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _flytrapper.x, _probeY31, 20, 20);
		RectangleMakeCenter(getMemDC(), _flytrapper.x, _probeY32, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX41, _barbarian.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX42, _barbarian.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _barbarian.x, _probeY41, 20, 20);
		RectangleMakeCenter(getMemDC(), _barbarian.x, _probeY42, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX51, _devilBomber.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _probeX52, _devilBomber.y, 20, 20);
		RectangleMakeCenter(getMemDC(), _devilBomber.x, _probeY51, 20, 20);
		RectangleMakeCenter(getMemDC(), _devilBomber.x, _probeY52, 20, 20);
	}
}
