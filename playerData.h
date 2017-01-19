#pragma once
#include "singletonBase.h"
class item;
struct tagMonster
{
	float x, y;
};

class playerData : public singletonBase <playerData>
{
private:

	bool _isSlimeDie;
	bool _isFluffyBugDie;
	bool _isFlytrapperDie;
	bool _isBarbarianDie;
	bool _isDevilBomberDie;
	bool _isBossDie;

	int _monsterNumber;

	float _backX;
	float _backY;


	float _npcX;
	float _npcY;

	tagMonster _monster;
	tagMonster _slime;
	tagMonster _fluffyBug;
	tagMonster _barbarian;
	tagMonster _flytrapper;
	tagMonster _devilBomber;

	tagMonster _player;
	float _bgX;
	float _bgY;
private:
	int _money;
	vector<item*> _vInvenWeapon;
	vector<item*> _vInvenEquip;
	vector<item*> _vInvenPotion;

	int _Alexatt;
	int _Alexdef;
	int _Alexcurrenthp;
	int _AlexMaxhp;
	int _Alexcurrentmp;
	int _AlexMaxmp;
	item* _AlexWeaponitem;
	item* _AlexEquipitem;

	int _Tematt;
	int _Temdef;
	int _Temcurrenthp;
	int _TemMaxhp;
	int _Temcurrentmp;
	int _TemMaxmp;
	item* _TemWeaponitem;
	item* _TemEquipitem;

	int _Lunaatt;
	int _Lunadef;
	int _Lunacurrenthp;
	int _LunaMaxhp;
	int _Lunacurrentmp;
	int _LunaMaxmp;
	item* _LunaWeaponitem;
	item* _LunaEquipitem;
public:
	int getMoney() { return _money; }
	void setMoney(int set) { _money = set; }

	int getAlexatt() { return _Alexatt; }
	void setAlexatt(int set) { _Alexatt = set; }
	int getAlexdef() { return _Alexdef; }
	void setAlexdef(int set) { _Alexdef = set; }
	int getAlexcurrenthp() { return _Alexcurrenthp; }
	void setAlexcurrenthp(int set) { _Alexcurrenthp = set; }
	int getAlexcurrentmp() { return _Alexcurrentmp; }
	void setAlexcurrentmp(int set) { _Alexcurrentmp = set; }
	int getAlexMaxhp() { return _AlexMaxhp; }
	void setAlexMaxhp(int set) { _AlexMaxhp = set; }
	int getAlexMaxmp() { return _AlexMaxmp; }
	void setAlexMaxmp(int set) { _AlexMaxmp = set; }
	item* getAlexWeaponitem() { return _AlexWeaponitem; }
	void setAlexWeapoonitem(item* set) { _AlexWeaponitem = set; }
	item* getAlexEquipeitem() { return _AlexEquipitem; }
	void setAlexEquipitem(item* set) { _AlexEquipitem = set; }

	int getTematt() { return _Tematt; }
	void setTematt(int set) { _Tematt = set; }
	int getTemdef() { return _Temdef; }
	void setTemdef(int set) { _Temdef = set; }
	int getTemcurrenthp() { return _Temcurrenthp; }
	void setTemcurrenthp(int set) { _Temcurrenthp = set; }
	int getTemcurrentmp() { return _Temcurrentmp; }
	void setTemcurrentmp(int set) { _Temcurrentmp = set; }
	int getTemMaxhp() { return _TemMaxhp; }
	void setTemMaxhp(int set) { _TemMaxhp = set; }
	int getTemMaxmp() { return _TemMaxmp; }
	void setTemMaxmp(int set) { _TemMaxmp = set; }
	item* getTemWeaponitem() { return _TemWeaponitem; }
	void setTemWeapoonitem(item* set) { _TemWeaponitem = set; }
	item* getTemEquipeitem() { return _TemEquipitem; }
	void setTemEquipitem(item* set) { _TemEquipitem = set; }

	int getLunaatt() { return _Lunaatt; }
	void setLunaatt(int set) { _Lunaatt = set; }
	int getLunadef() { return _Lunadef; }
	void setLunadef(int set) { _Lunadef = set; }
	int getLunacurrenthp() { return _Lunacurrenthp; }
	void setLunacurrenthp(int set) { _Lunacurrenthp = set; }
	int getLunacurrentmp() { return _Lunacurrentmp; }
	void setLunacurrentmp(int set) { _Lunacurrentmp = set; }
	int getLunaMaxhp() { return _LunaMaxhp; }
	void setLunaMaxhp(int set) { _LunaMaxhp = set; }
	int getLunaMaxmp() { return _LunaMaxmp; }
	void setLunaMaxmp(int set) { _LunaMaxmp = set; }
	item* getLunaWeaponitem() { return _LunaWeaponitem; }
	void setLunaWeapoonitem(item* set) { _LunaWeaponitem = set; }
	item* getLunaEquipeitem() { return _LunaEquipitem; }
	void setLunaEquipitem(item* set) { _LunaEquipitem = set; }

	vector<item*> getInvenWeapon() { return _vInvenWeapon; }
	vector<item*> getInvenEquip() { return _vInvenEquip; }
	vector<item*> getInvenPotion() { return _vInvenPotion; }
	void setInvenWeapon(item* weaponItem)
	{
		_vInvenWeapon.push_back(weaponItem);
	}
	void setInvenEquip(item* equipItem)
	{
		_vInvenEquip.push_back(equipItem);
	}
	void setInvenPotion(item* potionItem)
	{
		_vInvenPotion.push_back(potionItem);
	}

	void RemoveWeapon() { _vInvenWeapon.clear(); }
	void RemoveEquip() { _vInvenEquip.clear(); }
	void RemovePotion() { _vInvenPotion.clear(); }

public:
	HRESULT init(void);
	void release(void);

	bool getSlimeDie() { return _isSlimeDie; }
	void setSlimeDie(bool isSlimeDie) { _isSlimeDie = isSlimeDie; }
	bool getFluffyBugDie() { return _isFluffyBugDie; }
	void setFluffyBugDie(bool sFluffyBugDie) { _isFluffyBugDie = sFluffyBugDie; }
	bool getFlytrapperDie() { return _isFlytrapperDie; }
	void setFlytrapperDie(bool isFlytrapperDie) { _isFlytrapperDie = isFlytrapperDie; }
	bool getBarbarianDie() { return _isBarbarianDie; }
	void setBarbarianDie(bool isBarbarianDie) { _isBarbarianDie = isBarbarianDie; }
	bool getDevilBomberDie() { return _isDevilBomberDie; }
	void setDevilBomberDie(bool isDevilBomberDie) { _isDevilBomberDie = isDevilBomberDie; }
	bool getBossDie() { return _isBossDie; }
	void setBossDie(bool isBossDie) { _isBossDie = isBossDie; }

	void setMonsterNumber(int monsterNumber) { _monsterNumber = monsterNumber; }
	int getMonsterNumber() { return _monsterNumber; }

	float getMonsterX() { return _monster.x; }
	float getMonsterY() { return _monster.y; }
	void setMonsterX(float x) { _monster.x = x; }
	void setMonsterY(float y) { _monster.y = y; }

	int getBackX() { return _backX; }
	int getBackY() { return _backY; }
	void setBackX(float x) { _backX = x; }
	void setBackY(float y) { _backY = y; }

	float getSlimeX() { return _slime.x; }
	float getSlimeY() { return _slime.y; }
	void setSlimeX(float x) { _slime.x = x; }
	void setSlimeY(float y) { _slime.y = y; }

	float getFluffyBugX() { return _fluffyBug.x; }
	float getFluffyBugY() { return _fluffyBug.y; }
	void setFluffyBugX(float x) { _fluffyBug.x = x; }
	void setFluffyBugY(float y) { _fluffyBug.y = y; }

	float getFlytrapperX() { return _flytrapper.x; }
	float getFlytrapperY() { return _flytrapper.y; }
	void setFlytrapperX(float x) { _flytrapper.x = x; }
	void setFlytrapperY(float y) { _flytrapper.y = y; }

	float getBarbarianX() { return _barbarian.x; }
	float getBarbarianY() { return _barbarian.y; }
	void setBarbarianX(float x) { _barbarian.x = x; }
	void setBarbarianY(float y) { _barbarian.y = y; }

	float getDevilBomberX() { return _devilBomber.x; }
	float getDevilBomberY() { return _devilBomber.y; }
	void setDevilBomberX(float x) { _devilBomber.x = x; }
	void setDevilBomberY(float y) { _devilBomber.y = y; }

	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }

	float getBgX() { return _bgX; }
	float getBgY() { return _bgY; }
	void setBgX(float x) { _bgX = x; }
	void setBgY(float y) { _bgY = y; }

	float getNpcX() { return _npcX; }
	void setNpcX(float x) { _npcX = x; }
	float getNpcY() { return _npcY; }
	void setNpcY(float y) { _npcY = y; }

	playerData() {}
	~playerData() {}
};

