#pragma once
#include "gameNode.h"

struct tagMONSTER
{
	float x, y;
	float angle;
	float moveSpeed;
	float w, h;
	int currentFrameX;
	int currentFrameY;
	RECT rc;
	RECT rcExplore;

	bool isDie;
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
};

class owDungeon : public gameNode
{
private:
	tagMONSTER _monster;
	tagMONSTER _slime;
	tagMONSTER _fluffyBug;
	tagMONSTER _flytrapper;
	tagMONSTER _barbarian;
	tagMONSTER _devilBomber;
	int _time;
	int _monsterNumber;

	float _backX;
	float _backY;

	float _probeX01;
	float _probeX02;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY01;
	float _probeY02;

	bool isLeftCollision0;
	bool isRightCollision0;
	bool isUpCollision0;
	bool isDownCollision0;

	float _probeX11;
	float _probeX12;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY11;
	float _probeY12;

	bool isLeftCollision1;
	bool isRightCollision1;
	bool isUpCollision1;
	bool isDownCollision1;

	float _probeX21;
	float _probeX22;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY21;
	float _probeY22;

	bool isLeftCollision2;
	bool isRightCollision2;
	bool isUpCollision2;
	bool isDownCollision2;

	float _probeX31;
	float _probeX32;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY31;
	float _probeY32;

	bool isLeftCollision3;
	bool isRightCollision3;
	bool isUpCollision3;
	bool isDownCollision3;

	float _probeX41;
	float _probeX42;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY41;
	float _probeY42;

	bool isLeftCollision4;
	bool isRightCollision4;
	bool isUpCollision4;
	bool isDownCollision4;

	float _probeX51;
	float _probeX52;			//ÇÈ¼¿Ãæµ¹ Å½ÁöÇÒ y°ª
	float _probeY51;
	float _probeY52;

	bool isLeftCollision5;
	bool isRightCollision5;
	bool isUpCollision5;
	bool isDownCollision5;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setSlimeX(float x) { _slime.x = x; }
	void setFluffyBugX(float x) { _fluffyBug.x = x; }
	void setFlytrapperX(float x) { _flytrapper.x = x; }
	void setBarbarianX(float x) { _barbarian.x = x; }
	void setDevilBomberX(float x) { _devilBomber.x = x; }

	int getMonsterNumber() { return _monsterNumber; }

	owDungeon() {}
	~owDungeon() {}
};

