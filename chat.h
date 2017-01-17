#pragma once
#include "gameNode.h"
class chat : public gameNode
{
private:
	int _x, _y;
	int _count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void AlthenaChat();
	void kidsChat();
	void misterChat();
	void setCount(int count) { _count = count; }
	int getCount() { return _count; }

	chat() {}
	~chat() {}
};
