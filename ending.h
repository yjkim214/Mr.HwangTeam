#pragma once
#include "gameNode.h"
class ending : public gameNode
{
private:
	image* _ending;
	int FrameX;
	int count;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ending() {}
	~ending() {}
};

