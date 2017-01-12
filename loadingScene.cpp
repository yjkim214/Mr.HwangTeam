#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	if (_loading->loadingDone())
	{
		//�ε��� �Ϸ� ������ ������
		SCENEMANAGER->changeScene("���θ޴�");
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ ����� ����
	/*for (int i = 0; i < 10; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}*/

//ȭ��
	_loading->loadImage("arrow", "arrow.bmp", 112, 48, true, RGB(255, 0, 0));	

//�ʵ�
	_loading->loadImage("BossRoom", "BossRoom.bmp", 800, 1000, true, RGB(255, 0, 255));								
	_loading->loadImage("BossRoomSky", "BossRoomSky.bmp", 800, 1000, true, RGB(255, 0, 255));						
	_loading->loadImage("hotel1", "hotel1.bmp", 800, 600, true,RGB(255,0,255));										
	_loading->loadImage("hotel2", "hotel2.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house1", "house1.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house2", "house2.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house3", "house3.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house4", "house4.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("mouseCursor", "mouseCursor.bmp", 23, 30, true, RGB(255, 0, 255));							
	_loading->loadImage("shop", "shop.bmp", 800, 600, true, RGB(255, 0, 255));										
	_loading->loadImage("strore", "strore.bmp", 500, 458, true, RGB(255, 0, 255));

//���ķ��� ��ų �ǹ���(��Ʈ����???) 
	_loading->loadImage("dungeon_tree", "dungeon_tree.bmp", 1600, 1200, true, RGB(255, 0, 255));
	_loading->loadImage("village_building", "village_building.bmp", 1600, 1200, true, RGB(255, 0, 255));
	_loading->loadImage("village_in", "village_in.bmp", 1600, 1200, true, RGB(255, 0, 255));

//���θ޴� �� �� �ʵ� �ȼ��浹�Ҹʵ� 	
	_loading->loadImage("loadSelect", "loadSelect.bmp", 800, 600,false);											
	_loading->loadImage("mainMenu", "mainMenu.bmp", 800, 600, false);												
	_loading->loadImage("newGameSelect", "newGameSelect.bmp", 800, 600, false);										
	_loading->loadImage("village", "village.bmp", 1600, 1200,false);												
	_loading->loadImage("dungeon", "dungeon.bmp", 1600, 1200, false);												
	_loading->loadImage("exitSelect", "exitSelect.bmp", 800, 600, false);											
	_loading->loadImage("BossRoomPixel", "BossRoomPixel.bmp", 800, 1000, false);
	_loading->loadImage("BossRoomPixel", "BossRoomPixel.bmp", 800, 1000, false);
	_loading->loadImage("dungeonPixel", "dungeonPixel.bmp", 1600, 1200, false);
	_loading->loadImage("hotel1Pixel", "hotel1Pixel.bmp", 800, 600, false);
	_loading->loadImage("hotel2Pixel", "hotel2Pixel.bmp", 800, 600, false);
	_loading->loadImage("house1Pixel", "house1Pixel.bmp", 800, 600, false);
	_loading->loadImage("house2Pixel", "house2Pixel.bmp", 800, 600, false);
	_loading->loadImage("house3Pixel", "house3Pixel.bmp", 800, 600, false);
	_loading->loadImage("house4Pixel", "house4Pixel.bmp", 800, 600, false);
	_loading->loadImage("shopPixel", "shopPixel.bmp", 800, 600, false);
	_loading->loadImage("strorePixel", "strorePixel.bmp", 500, 458, false);
	_loading->loadImage("villagePixel", "villagePixel.bmp", 1600, 1200, false);

// ���佺Ʈ(Ȱ) �ִϸ��̼� 
	_loading->loadFrameImage("TempestAction_ IDLE", "TempestAction_ IDLE.bmp", 188, 124, 2,1,true, RGB(255, 0, 255));  
	_loading->loadFrameImage("TempestAction_WALK", "TempestAction_WALK.bmp", 188, 124,5,1, true, RGB(255, 0, 255));	  
	_loading->loadFrameImage("TempestDown", "TempestDown.bmp", 120, 63, 5, 1, true, RGB(255, 0, 255));				  
	_loading->loadFrameImage("TempestLeft", "TempestLeft.bmp", 155, 62, 5, 1, true, RGB(255, 0, 255));				  
	_loading->loadFrameImage("TempestRight", "TempestRight.bmp", 155, 62, 5, 1, true, RGB(255, 0, 255));			  
	_loading->loadFrameImage("TempestUp", "TempestUp.bmp", 110, 59, 5, 1, true, RGB(255, 0, 255));					  
	_loading->loadFrameImage("TempsetAction", "TempsetAction.bmp", 500, 160, 5, 1, true, RGB(255, 0, 255));			  
	_loading->loadFrameImage("winTempest", "winTempest.bmp", 310, 124, 5, 1, true, RGB(255, 0, 255));	
	_loading->loadImage("dieTempest", "dieTempest.bmp", 110, 64, true, RGB(255, 0, 255));
																													  
//��Ʋȭ�� ������ �ִϸ��̼�
	_loading->loadFrameImage("slime_idle", "slime_idle.bmp", 180, 60, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_attack", "slime_attack.bmp", 345, 64, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_getdmg", "slime_getdmg.bmp", 120, 52, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_dead", "slime_dead", 60, 60, 1, 1, true, RGB(255, 0, 255));

	//���� �������� ����
	_loading->loadFrameImage("slime", "slime.bmp", 180, 60, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBugUp", "fluffyBugUp.bmp", 120, 48, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBugRight", "fluffyBugRight.bmp", 162, 49, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBugDown", "fluffyBugDown.bmp", 120, 48, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBugLeft", "fluffyBugLeft.bmp", 162, 49, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapperUp", "flytrapperUp.bmp", 246, 90, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapperRight", "flytrapperRight.bmp", 294, 83, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapperDown", "flytrapperDown.bmp", 255, 87, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapperLeft", "flytrapperLeft.bmp", 294, 83, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarianUp", "barbarianUp.bmp", 162, 73, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarianRight", "barbarianRight.bmp", 204, 76, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarianDown", "barbarianDown.bmp", 162, 69, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarianLeft", "barbarianLeft.bmp", 204, 76, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomberUp", "devilBomberUp.bmp", 304, 68, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomberRight", "devilBomberRight.bmp", 268, 66, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomberDown", "devilBomberDown.bmp", 296, 68, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomberLeft", "devilBomberLeft.bmp", 268, 66, 4, 1, true, RGB(255, 0, 255));

	//�糪 �ɸ��� �������� �� ��Ʋ
	_loading->loadFrameImage("lunarSkillEffect", "lunarSkillEffect.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarAttacked", "lunarAttacked.bmp", 400, 500, 32, 54, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarDeath", "lunarDeath.bmp", 450, 500, 54, 34, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarMoveUp", "lunarMoveUp.bmp", 300, 300, 110, 59, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarMoveDown", "lunarMoveDown.bmp", 300, 300, 110, 59, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarMoveLeft", "lunarMoveLeft.bmp", 300, 300, 135, 58, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarMoveRight", "lunarMoveRight.bmp", 300, 300, 135, 59, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarSkillWait", "lunarSkillWait.bmp", 400, 400, 204, 41, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarSkillMotion", "lunarSkillMotion.bmp", 450, 400, 259, 62, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarWait", "lunarWait.bmp", 500, 400, 174, 54, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarWaitStaff", "lunarWaitStaff.bmp", 600, 400, 228, 54, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarWaitStaff", "lunarWaitStaff.bmp", 600, 400, 228, 54, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("lunarVictory", "lunarVictory.bmp", 650, 400, 162, 57, 6, 1, true, RGB(255, 0, 255));


	//���¿��� �÷��̾�
	_loading->loadFrameImage("owPlayer_idle", "owPlayer_idle.bmp", 120, 65, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("owPlayer_move", "owPlayer_move.bmp", 120, 260, 4, 4, true, RGB(255, 0, 255));


}


//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
}
