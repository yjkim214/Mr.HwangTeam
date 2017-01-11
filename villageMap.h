#pragma once
#include "gameNode.h"
class villageMap :	public gameNode
{
private:
	int _bgX;
	int _bgY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getBgX() { return _bgX; }
	void setBgX(int bgX) { _bgX = bgX; }
	int getBgY() { return _bgY; }
	void setBgY(int bgY) { _bgY = bgY; }
	villageMap() {}
	~villageMap() {}
};

