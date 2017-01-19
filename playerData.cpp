#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init(void)
{
	_isSlimeDie = false;
	_isFluffyBugDie = false;
	_isFlytrapperDie = false;
	_isBarbarianDie = false;
	_isDevilBomberDie = false;
	_isBossDie = false;

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
	_money = 3000;
	//
	_Alexatt = 10;
	_Alexdef = 10;
	_Alexcurrenthp = 80;
	_AlexMaxhp = 100;
	_Alexcurrentmp = 100;
	_AlexMaxmp = 100;
	_AlexWeaponitem = NULL;
	_AlexEquipitem = NULL;

	//temp hp
	_Tematt = 15;
	_Temdef = 5;
	_Temcurrenthp = 100;
	_Temcurrentmp = 100;
	_TemMaxhp = 100;
	_TemMaxmp = 100;
	_TemWeaponitem = NULL;
	_TemEquipitem = NULL;

	// luna hp
	_Lunaatt = 5;
	_Lunadef = 10;
	_Lunacurrenthp = 100;
	_Lunacurrentmp = 100;
	_LunaMaxhp = 100;
	_LunaMaxmp = 100;
	_LunaWeaponitem = NULL;
	_LunaEquipitem = NULL;


	return S_OK;
}

void playerData::release(void)
{
}
