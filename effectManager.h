#pragma once
#include "singletonBase.h"

struct tagEffect
{
	RECT _rc;
	float _x, _y;
	float _width, _height;
	int _currentFrameX;
	int _count;

	image* _effectImg;
};

class effectManager : public singletonBase<effectManager>
{
private:
	vector<tagEffect> _vEffect;

public:
	void addEffect(float x, float y, char* effectImageKey);
	void update();
	void render(HDC hdc);

	effectManager() {}
	~effectManager() {}
};