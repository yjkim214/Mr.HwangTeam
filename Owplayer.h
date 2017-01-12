#pragma once
#include "gameNode.h"


class villageMap;

enum state
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

class Owplayer : public gameNode
{
private:
	villageMap* _Scene;
	state _state;
	Lookat _lookat;
	image* _playerImg;
	float _x, _y;
	float _speed;
	int _att;
	int _dex;
	int _animcount;
	RECT _camera;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//상호 참조하기위해 만들어놓은 함수
	void setScene(villageMap* Scene) { _Scene = Scene; }

	void playerstate();
	void playersetstate();
	void animation();


	//겟셋함수 만들어놓기
	image* getPlayerImg() { return _playerImg; }
	void setPlayerImg(image* playerImg) { _playerImg = playerImg; }
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	Lookat getLookat() { return _lookat; }
	void setLookat(Lookat lookat) { _lookat = lookat; }


	Owplayer() {}
	~Owplayer() {}
};

