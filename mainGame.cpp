#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## init(void) ## �ʱ�ȭ
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	
	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 �����Ѵ�
	//�׸��� ������ ������ ���ΰ��ӿ����� �ϸ� �ȴ�
	/*���߰�*/
	_mainMenu = new mainMenuScene;
	_villageScene = new villageScene;
	SCENEMANAGER->addScene("���׽�Ʈ", new sceneTest);
	SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
	SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("����", new soundTestScene);
	SCENEMANAGER->addScene("���θ޴�", _mainMenu);
	SCENEMANAGER->addScene("��Ʈ��", new introScene);
	SCENEMANAGER->addScene("����", _villageScene);
	SCENEMANAGER->addScene("��Ʋȭ��", new battleScene);
	SCENEMANAGER->addScene("����", new owDungeon);

	_villageScene->setMain(_mainMenu);

	/*����� ����*/
	SCENEMANAGER->changeScene("��Ʈ��");

	return S_OK;
}
//=============================================================
//	## release(void) ## ����
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}
//=============================================================
//	## update(void) ## ������Ʈ
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}
//=============================================================
//	## render(void) ## ����
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (������ �׳� �״�� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	
	//���Ŵ��� ����
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render(getMemDC());
	}

	IMAGEMANAGER->render("mouseCursor", getMemDC(), _ptMouse.x, _ptMouse.y);

//=============================================================
	//������� ������ HDC�� �׸��� (������ �״�� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}