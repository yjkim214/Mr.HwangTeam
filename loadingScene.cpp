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
	_loading->loadImage("BossRoomSky", "BossRoomSky.bmp", 800, 1200, true, RGB(255, 0, 255));						
	_loading->loadImage("hotel1", "hotel1.bmp", 800, 600, true,RGB(255,0,255));										
	_loading->loadImage("hotel2", "hotel2.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house1", "house1.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house2", "house2.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house3", "house3.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("house4", "house4.bmp", 800, 600, true, RGB(255, 0, 255));									
	_loading->loadImage("mouseCursor", "mouseCursor.bmp", 23, 30, true, RGB(255, 0, 255));							
	_loading->loadImage("shop", "shop.bmp", 800, 600, true, RGB(255, 0, 255));										
	_loading->loadImage("strore", "strore.bmp", 800, 600, true, RGB(255, 0, 255));

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
	_loading->loadImage("dungeonPixel", "dungeonPixel.bmp", 1600, 1200, false);
	_loading->loadImage("hotel1Pixel", "hotel1Pixel.bmp", 800, 600, false);
	_loading->loadImage("hotel2Pixel", "hotel2Pixel.bmp", 800, 600, false);
	_loading->loadImage("house1Pixel", "house1Pixel.bmp", 800, 600, false);
	_loading->loadImage("house2Pixel", "house2Pixel.bmp", 800, 600, false);
	_loading->loadImage("house3Pixel", "house3Pixel.bmp", 800, 600, false);
	_loading->loadImage("house4Pixel", "house4Pixel.bmp", 800, 600, false);
	_loading->loadImage("shopPixel", "shopPixel.bmp", 800, 600, false);
	_loading->loadImage("strorePixel", "strorePixel.bmp", 800, 600, false);
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


	// �κ��丮
	_loading->loadFrameImage("inven", "inven.bmp", 480, 172, 4, 1, true, RGB(255, 0, 255));

	//NPC
	_loading->loadFrameImage("NPC book", "NPC book.bmp", 132, 52, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NPCkid", "NPCkid.bmp", 132, 96, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NPCkidW", "NPCkidW.bmp", 150, 96, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NPCW", "NPCW.bmp", 188, 85, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NPCWalpha", "NPCWalpha.bmp", 188, 64, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SHOP(NPC)", "SHOP(NPC).bmp", 205, 68, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SHOP(NPC)back", "SHOP(NPC)back.bmp", 225, 70, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage("Althena", "Althena.bmp", 227, 300, true, RGB(255, 0, 255));
	_loading->loadImage("AlthenaText", "AlthenaText.bmp", 131, 30, true, RGB(255, 0, 255));

	//��Ʋȭ�� ������ �ִϸ��̼�
	_loading->loadFrameImage("slime_idle", "slime_idle.bmp", 450, 150, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_attack", "slime_attack.bmp", 750, 150, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_getdmg", "slime_getdmg.bmp", 300, 150, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("slime_dead", "slime_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� �÷��ǹ��� �ִϸ��̼�
	_loading->loadFrameImage("fluffyBug_idle", "fluffyBug_idle.bmp", 450, 150, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBug_attack", "fluffyBug_attack.bmp", 750, 150, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBug_getdmg", "fluffyBug_getdmg.bmp", 300, 150, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fluffyBug_dead", "fluffyBug_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� �ö���Ʈ���� �ִϸ��̼�
	_loading->loadFrameImage("flytrapper_idle", "flytrapper_idle.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapper_attack", "flytrapper_attack.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapper_getdmg", "flytrapper_getdmg.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapper_dead", "flytrapper_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flytrapper_skill", "flytrapper_skill.bmp", 1050, 150, 7, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� �ٹٸ��� �ִϸ��̼�
	_loading->loadFrameImage("barbarian_idle", "barbarian_idle.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarian_attack", "barbarian_attack.bmp", 900, 150, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarian_getdmg", "barbarian_getdmg.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("barbarian_dead", "barbarian_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� ����չ� �ִϸ��̼�
	_loading->loadFrameImage("devilBomber_idle", "devilBomber_idle.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomber_attack", "devilBomber_attack.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomber_getdmg", "devilBomber_getdmg.bmp", 300, 150, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomber_dead", "devilBomber_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("devilBomber_skill", "devilBomber_skill.bmp", 1500, 150, 10, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� UI �̹���
	_loading->loadImage("bsUi_Attack", "bsUi_Attack.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Skill", "bsUi_Skill.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Defense", "bsUi_Defense.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Getaway", "bsUi_Getaway.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("bsUi_Attack_Selected", "bsUi_Attack_Selected.bmp", 66, 66, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Skill_Selected", "bsUi_Skill_Selected.bmp", 66, 66, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Defense_Selected", "bsUi_Defense_Selected.bmp", 66, 66, true, RGB(255, 0, 255));
	_loading->loadImage("bsUi_Getaway_Selected", "bsUi_Getaway_Selected.bmp", 66, 66, true, RGB(255, 0, 255));

	//��Ʋȭ�� �˷��� �̹���
	_loading->loadFrameImage("bsAlex_idle@2", "bsAlex_idle@2.bmp", 750, 150, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_attack@2", "bsAlex_attack@2.bmp", 1350, 150, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_skill@2", "bsAlex_skill@2.bmp", 7830, 150, 29, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_defense@2", "bsAlex_defense@2.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_dead@2", "bsAlex_dead@2.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_getdmg@2", "bsAlex_getdmg@2.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsAlex_victory@2", "bsAlex_victory@2.bmp", 1200, 150, 8, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� �糪 �̹���
	_loading->loadFrameImage("bsLunar_idle", "bsLunar_idle.bmp", 900, 150, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_attack", "bsLunar_attack.bmp", 1500, 150, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_skill", "bsLunar_skill.bmp", 1050, 150, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_defense", "bsLunar_defense.bmp", 450, 150, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_dead", "bsLunar_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_getdmg", "bsLunar_getdmg.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_victory", "bsLunar_victory.bmp", 900, 150, 6, 1, true, RGB(255, 0, 255));

	//��Ʋȭ�� ���佺Ʈ �̹���
	_loading->loadFrameImage("bsTempest_idle", "bsTempest_idle.bmp", 600, 150, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_attack", "bsTempest_attack.bmp", 750, 150, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_skill", "bsTempest_skill.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_defense", "bsTempest_defense.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_dead", "bsTempest_dead.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_getdmg", "bsTempest_getdmg.bmp", 150, 150, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsTempest_victory", "bsTempest_victory.bmp", 750, 150, 5, 1, true, RGB(255, 0, 255));

	//���佺Ʈ ��ų ����Ʈ
	_loading->loadFrameImage("bsTempest_skilEffect", "bsTempest_skilEffect.bmp", 1240, 30, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsEffect_attack", "bsEffect_attack.bmp", 105, 40, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bsLunar_skillEffect", "bsLunar_skillEffect.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));

	//��Ʋ�� ���ȭ��
	_loading->loadImage("bsBackground01", "bsBackground01.bmp", 800, 600);
	_loading->loadImage("bsBackground02", "bsBackground02.bmp", 800, 600);
	
	//��Ʋ�� UI
	_loading->loadImage("bsAlex_Ui", "bsAlex_Ui.bmp", 150, 135, true, RGB(255, 0, 255));
	_loading->loadImage("bsLunar_Ui", "bsLunar_Ui.bmp", 150, 135, true, RGB(255, 0, 255));
	_loading->loadImage("bsTempest_Ui", "bsTempest_Ui.bmp", 150, 135, true, RGB(255, 0, 255));

	//��ȭâ UI
	_loading->loadImage("chat", "chat.bmp", 600, 200, true, RGB(255, 0, 255));

	//�޴� ���� 
	_loading->loadImage("menu", "menu.bmp", 800, 600, true, RGB(255, 0, 255));
	_loading->loadImage("saveSelect", "saveSelect.bmp", 800, 600, true, RGB(255, 0, 255));
	_loading->loadImage("menuSelect", "menuSelect.bmp", 800, 600, true, RGB(255, 0, 255));
}


//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
	//���� �߰�
	_loading->loadSound("villageMusic", "villageMusic.MID", true, true);
	_loading->loadSound("����ver2", "����ver2.MID", true, true);
	_loading->loadSound("mainMenuSound", "mainMenuSound.MID", true, true);
	_loading->loadSound("dungeonSound", "dungeonSound.MID", true, true);
	_loading->loadSound("bossRoomSound", "bossRoomSound.MID", true, true);
	_loading->loadSound("NPCchatMusic", "NPCchatMusic.WAV");
	_loading->loadSound("battleMusic", "battleMusic.MID",true,true);
}

