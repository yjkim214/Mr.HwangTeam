#pragma once
#include "singletonBase.h"

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

