#include "gameNode.h"

class bsPlayer;
class AlexNoah; 
class Lunar;
class Tempest;

class bsPlayerManager : public gameNode
{
private:
	vector<bsPlayer*> _vPlayerList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void addAlexNoah(float prevX, float prevY);
	void addLunar(float prevX, float prevY);
	void addTempest(float prevX, float prevY);

public:
	vector<bsPlayer*> getVPlayerList() { return _vPlayerList; }

	bsPlayerManager() {}
	~bsPlayerManager() {}
};