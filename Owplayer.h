#pragma once
#include "gameNode.h"

class villageMap;
class inventory;
class item;
class progressBar;
class NPC;

enum OWPLAYER_STATE
{
	IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
};

enum Lookat
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
};

enum OWPLAYER_Character
{
	ALEX,
	TEMP,
	LUNAR
};

class Owplayer : public gameNode
{
private:
	float _ptPrevX, _ptPrevY;
	villageMap* _Scene;
	inventory* _inventory;
	item* _item;
	NPC* _npc;
	progressBar* _hp;
	progressBar* _mp;
	//alex
	vector<item*> _vWeaponlist;
	vector<item*> _vIEquiplist;
	//tem
	vector<item*> _vTemWeaponlist;
	vector<item*> _vTemEquiplist;
	//luna
	vector<item*> _vLunaWeaponlist;
	vector<item*> _vLunaEquiplist;

	image* _statusimg;
	image* _statusmenuimg;
	HFONT font;


	OWPLAYER_STATE _state;
	Lookat _lookat;
	image* _playerImg;
	OWPLAYER_Character _character;
	float _x, _y;
	float _speed;
	int _animcount;
	bool _shopopen;
	//aelx
	int _AlexcurrentHp;
	int _AlexMaxHp;
	int _AlexcurrentMp;
	int _AlexMaxMp;

	int _AlexAtt;
	int _AlexDef;
	int _AlexMatt;

	//temp
	int _TemcurrentHp;
	int _TemMaxHp;
	int _TemcurrentMp;
	int _TemMaxMp;

	int _TemAtt;
	int _TemDef;
	int _TemMatt;

	//luna
	int _lunacurrentHp;
	int _lunaMaxHp;
	int _lunacurrentMp;
	int _lunaMaxMp;

	int _LunaAtt;
	int _LunaDef;
	int _LunaMatt;


	RECT _camera;
	int _money;
	//alex
	bool _isWeapon;
	bool _isEquip;
	//tem
	bool _isTemWeapon;
	bool _isTemEquip;
	//luna
	bool _islunaWeapon;
	bool _islunaEquip;


	int _proveLeft;
	int _proveRight;
	int _proveUp;
	int _proveDown;




public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void invenrender(void);

	//alex 

	void equipstate(void);

	//tem
	void temequipstate(void);

	//luna
	void lunaequipstate(void);

	//상호 참조하기위해 만들어놓은 함수
	void setScene(villageMap* Scene) { _Scene = Scene; }
	void playerstate();
	void playersetstate();
	void animation();

	void ProveUpdate();

	//겟셋함수 만들어놓기
	image* getPlayerImg() { return _playerImg; }
	void setPlayerImg(image* playerImg) { _playerImg = playerImg; }
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	Lookat getLookat() { return _lookat; }
	void setLookat(Lookat lookat) { _lookat = lookat; }
	int getProveLeft() { return _proveLeft; }
	void setProveLeft(int proveLeft) { _proveLeft = proveLeft; }
	int getProveRight() { return _proveRight; }
	void setProveRight(int proveRight) { _proveRight = proveRight; }
	int getProveUp() { return _proveUp; }
	void setProveUp(int proveUp) { _proveUp = proveUp; }
	int getProveDown() { return _proveDown; }
	void setProveDown(int proveDown) { _proveDown = proveDown; }
	OWPLAYER_STATE getPlayerState() { return _state; }
	void setPlayerState(OWPLAYER_STATE set) { _state = set; }
	RECT getCamera() { return _camera; }
	float getSpeed() { return _speed; }
	inventory* getinventory() { return _inventory; }
	int getMoney() { return _money; }
	void setMoney(int money) { _money = money; }


	//this character
	OWPLAYER_Character getCharacter() { return _character; }

	// ALEX Equipe
	void addWeapon(char * imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getWeapon() { return _isWeapon; }
	void setWeapon(bool set) { _isWeapon = set; }
	void addEquip(char* imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getEquip() { return _isEquip; }
	void setEquip(bool set) { _isEquip = set; }

	int getAlexAtt() { return _AlexAtt; }
	void setAlexAtt(int set) { _AlexAtt = set; }
	int getAlexDef() { return _AlexDef; }
	void setAlexDef(int set) { _AlexDef = set; }
	int getAlexMatt() { return _AlexMatt; }
	void setAlexMatt(int set) { _AlexMatt = set; }

	int getAlexcurrenthp() { return _AlexcurrentHp; }
	void setAlexcurrenthp(int set) { _AlexcurrentHp = set; }
	int getAlexcurrentMp() { return _AlexcurrentMp; }
	void setAlexcurrentMp(int set) { _AlexcurrentMp = set; }
	int getAlexMaxhp() { return _AlexMaxHp; }
	void setAlexMaxhp(int set) { _AlexMaxHp = set; }
	int getAlexMaxmp() { return _AlexMaxMp; }
	void setAlexMaxmp(int set) { _AlexMaxMp = set; }


	//Temp Equipe
	void addTemWeapon(char* imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getTemWeapon() { return _isTemWeapon; }
	void setTemWeapon(bool set) { _isTemWeapon = set; }
	void addTemEquip(char*imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getTemEquip() { return _isTemEquip; }
	void setTemEquip(bool set) { _isTemEquip = set; }

	int getTemAtt() { return _TemAtt; }
	void setTemAtt(int set) { _TemAtt = set; }
	int getTemDef() { return _TemDef; }
	void setTemDef(int set) { _TemDef = set; }
	int getTemMatt() { return _TemMatt; }
	void setTemMatt(int set) { _TemMatt = set; }

	int getTemcurrenthp() { return _TemcurrentHp; }
	void setTemcurrenthp(int set) { _TemcurrentHp = set; }
	int getTemcurrentmp() { return _TemcurrentMp; }
	void setTemcurrentmp(int set) { _TemcurrentMp = set; }
	int getTemMaxhp() { return _TemMaxHp; }
	void setTemMaxhp(int set) { _TemMaxHp = set; }
	int getTemMaxmp() { return _TemMaxMp; }
	void setTemMaxmp(int set) { _TemMaxMp = set; }

	//Luna Equipe
	void addLunaWeapon(char* imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getLunaWeapon() { return _islunaWeapon; }
	void setLunaWeapon(bool set) { _islunaWeapon = set; }
	void addLunaEquip(char* imgKey, int att, int def, int matt, ITEM_KIND kind, int cost);
	bool getLunaEquip() { return _islunaEquip; }
	void setLunaEquip(bool set) { _islunaEquip = set; }

	int getLunaAtt() { return _LunaAtt; }
	void setLunaAtt(int set) { _LunaAtt = set; }
	int getLunaDef() { return _LunaDef; }
	void setLunaDef(int set) { _LunaDef = set; }
	int getLunaMatt() { return _LunaMatt; }
	void setLunaMatt(int set) { _LunaMatt = set; }

	int getLunacurrenthp() { return _lunacurrentHp; }
	void setLunacurrenthp(int set) { _lunacurrentHp = set; }
	int getLunacurrentmp() { return _lunacurrentMp; }
	void setLunacurrentmp(int set) { _lunacurrentMp = set; }
	int getLunaMaxhp() { return _lunaMaxHp; }
	void setLunaMaxhp(int set) { _lunaMaxHp = set; }
	int getLunaMaxmp() { return _lunaMaxMp; }
	void setLunaMaxmp(int set) { _lunaMaxMp = set; }

	void setnpc(NPC* npc) { _npc = npc; }

	void OpenMenu();
	void MenuUpdate();
	void Font();

	void saveData();
	Owplayer() {}
	~Owplayer() {}
};

