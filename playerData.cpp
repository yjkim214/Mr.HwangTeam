#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init(void)
{
	_isSlimeDie = false;
	_isFluffyBugDie = false;
	_isFlytrapperDie = false;
	_isBarbarianDie = false;
	_isDevilBomberDie = false;

	_monsterNumber = 0;

	_monster.x = 100;
	_monster.y = 150;
	_backX = 0;
	_backY = 0;

	_slime.x = 279;
	_slime.y = 619;

	_fluffyBug.x = 411;
	_fluffyBug.y = 1037;

	_flytrapper.x = 1420;
	_flytrapper.y = 1018;

	_barbarian.x = 711;
	_barbarian.y = 253;

	_devilBomber.x = 1191;
	_devilBomber.y = 219;

	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	_bgX = 0;
	_bgY = 0;

	_npcX = 750;
	_npcY = 600;


	return S_OK;
}

void playerData::release(void)
{
}
