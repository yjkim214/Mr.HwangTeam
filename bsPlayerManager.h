
#include "gameNode.h"
class bsPlayer;
class AlexNoah;
class bsPlayerManager : public gameNode
{
private:
	vector<bsPlayer*> _vPlayerList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addAlexNoah(float prevX, float prevY);

	vector<bsPlayer*> getVPlayerList() { return _vPlayerList; }

	bsPlayerManager() {}
	~bsPlayerManager() {}
};