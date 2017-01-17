#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## init(void) ## 초기화
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	
	//앞으로 메인게임 클래스 안에서는 씬들만 관리한다
	//그리고 각각의 씬들이 메인게임역할을 하면 된다
	/*씬추가*/
	_mainMenu = new mainMenuScene;
	_villageScene = new villageScene;
	SCENEMANAGER->addScene("씬테스트", new sceneTest);
	SCENEMANAGER->addScene("픽셀충돌", new pixelCollision);
	SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	SCENEMANAGER->addScene("사운드", new soundTestScene);
	SCENEMANAGER->addScene("메인메뉴", _mainMenu);
	SCENEMANAGER->addScene("인트로", new introScene);
	SCENEMANAGER->addScene("마을", _villageScene);
	SCENEMANAGER->addScene("배틀화면", new battleScene);
	SCENEMANAGER->addScene("던전", new owDungeon);

	_villageScene->setMain(_mainMenu);

	/*현재씬 설정*/
	SCENEMANAGER->changeScene("인트로");

	return S_OK;
}
//=============================================================
//	## release(void) ## 해제
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}
//=============================================================
//	## update(void) ## 업데이트
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//씬매니져 업데이트
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}
//=============================================================
//	## render(void) ## 렌더
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵 (렌더에 그냥 그대로 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	
	//씬매니져 렌더
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//타임매니져 렌더
		TIMEMANAGER->render(getMemDC());
	}

	IMAGEMANAGER->render("mouseCursor", getMemDC(), _ptMouse.x, _ptMouse.y);

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (렌더에 그대로 둘것!!)
	this->getBackBuffer()->render(getHDC());
}