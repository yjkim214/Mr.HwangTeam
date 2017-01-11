#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료 됐으니 씬변경
		SCENEMANAGER->changeScene("메인메뉴");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	for (int i = 0; i < 10; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

	_loading->loadImage("arrow", "arrow.bmp", 112, 48, true, RGB(255, 0, 0));
	_loading->loadImage("BossRoom", "BossRoom.bmp", 800, 1000, true, RGB(255, 0, 255));
	_loading->loadImage("BossRoomSky", "BossRoomSky.bmp", 800, 1000, true, RGB(255, 0, 255));
	_loading->loadImage("dieTempest", "dieTempest.bmp", 110, 64, true, RGB(255, 0, 255));
	_loading->loadImage("hotel1", "hotel1.bmp", 800, 700, true,RGB(255,0,255));
	_loading->loadImage("hotel2", "hotel2.bmp", 950, 700, true, RGB(255, 0, 255));
	_loading->loadImage("house1", "house1.bmp", 900, 700, true, RGB(255, 0, 255));
	_loading->loadImage("house2", "house2.bmp", 1000, 600, true, RGB(255, 0, 255));
	_loading->loadImage("house3", "house3.bmp", 1000, 700, true, RGB(255, 0, 255));
	_loading->loadImage("house4", "house4.bmp", 1200, 800, true, RGB(255, 0, 255));
	_loading->loadImage("mouseCursor", "mouseCursor.bmp", 23, 30, true, RGB(255, 0, 255));
	_loading->loadImage("shop", "shop.bmp", 800, 600, true, RGB(255, 0, 255));
	_loading->loadImage("strore", "strore.bmp", 500, 458, true, RGB(255, 0, 255));
	_loading->loadImage("loadSelect", "loadSelect.bmp", 800, 600,false);
	_loading->loadImage("mainMenu", "mainMenu.bmp", 800, 600, false);
	_loading->loadImage("newGameSelect", "newGameSelect.bmp", 800, 600, false);	
	_loading->loadImage("village", "village.bmp", 1600, 1200,false);
	_loading->loadImage("dungeon", "dungeon.bmp", 1600, 1200, false);
	_loading->loadImage("exitSelect", "exitSelect.bmp", 800, 600, false);
	_loading->loadFrameImage("TempestAction_ IDLE", "TempestAction_ IDLE.bmp", 188, 124, 2,1,true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempestAction_WALK", "TempestAction_WALK.bmp", 188, 124,5,1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempestDown", "TempestDown.bmp", 120, 63, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempestLeft", "TempestLeft.bmp", 155, 62, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempestRight", "TempestRight.bmp", 155, 62, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempestUp", "TempestUp.bmp", 110, 59, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TempsetAction", "TempsetAction.bmp", 500, 160, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("winTempest", "winTempest.bmp", 310, 124, 5, 1, true, RGB(255, 0, 255));


}
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
}
