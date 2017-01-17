#include "stdafx.h"
#include "loading.h"
//=============================================================
// ## loadItem ## (�ε������ Ŭ����)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, string soundName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_soundResource.keyName = keyName;
	_soundResource.soundName = soundName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;

}


//=============================================================
// ## loading ## (�ε� Ŭ����)
//=============================================================

HRESULT loading::init(void)
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "bgLoadingScene.bmp", WINSIZEX, WINSIZEY);
	_loadingnum = IMAGEMANAGER->addFrameImage("loadingnum", "num.bmp", 220, 30, 10, 1, true, RGB(255, 0, 255));
	_loadingPersent = IMAGEMANAGER->addImage("_loadingPersent", "%.bmp", 30, 21, true, RGB(255, 0, 255));
	//�ε��� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack", 50, 580, 700, 25);
	_loadingBar->setGauge(0, 0);
	//���� ������ �ʱ�ȭ
	_currentGauge = 0;
	isImage = false;

	//�ε�����
	//SOUNDMANAGER->addSound("loadingMusic", "loadingMusic.mid", true, true);
	//SOUNDMANAGER->play("loadingMusic");

	return S_OK;
}

void loading::release(void)
{
	//�ε��� ����
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//�ε��� ������Ʈ
	_loadingBar->update();
}

void loading::render(void)
{
	//��׶��� ����
	_background->render(getMemDC());

	//�ε��� ����
	_loadingBar->render();

	if ((_currentGauge * 100) / _vLoadItem.size() < 10)
	{
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 130, _loadingBar->getRect().top - 40, (_currentGauge * 100) / _vLoadItem.size(), 0);
		_loadingPersent->render(getMemDC(), WINSIZEX - 100, _loadingBar->getRect().top - 30);
	}
	if ((_currentGauge * 100) / _vLoadItem.size() >= 10 && (_currentGauge * 100) / _vLoadItem.size() < 100)
	{
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 160, _loadingBar->getRect().top - 40, (_currentGauge * 100) / _vLoadItem.size() / 10, 0);
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 130, _loadingBar->getRect().top - 40, (_currentGauge * 100) / _vLoadItem.size() % 10, 0);
		_loadingPersent->render(getMemDC(), WINSIZEX - 100, _loadingBar->getRect().top - 30);
	}
	if ((_currentGauge * 100) / _vLoadItem.size() >= 100)
	{
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 190, _loadingBar->getRect().top - 40, (_currentGauge * 100) / _vLoadItem.size() / 100, 0);
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 160, _loadingBar->getRect().top - 40, ((_currentGauge * 100) / _vLoadItem.size() % 100) / 10, 0);
		_loadingnum->frameRender(getMemDC(), WINSIZEX - 130, _loadingBar->getRect().top - 40, (_currentGauge * 100) / _vLoadItem.size() % 10, 0);
		_loadingPersent->render(getMemDC(), WINSIZEX - 100, _loadingBar->getRect().top - 30);
	}

	fileNameText();
}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, string soundName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->init(keyName, soundName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone(void)
{
	//�ε��� �Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		isImage = true;
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		isImage = true;
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		isImage = true;
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		isImage = true;
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		isImage = true;
	}
	break;

	case LOAD_KIND_SOUND:
	{
		tagSoundResource sound = item->getSoundResource();
		SOUNDMANAGER->addSound(sound.keyName, sound.soundName, sound.bgm, sound.loop);
		isImage = false;
	}
	break;
	}

	//ZeroMemory(imgDir, sizeof(imgDir));
	ZeroMemory(Dir, sizeof(Dir));
	ZeroMemory(imgStr, sizeof(imgStr));
	ZeroMemory(soundStr, sizeof(soundStr));
	GetCurrentDirectory(1024, Dir);
	//GetCurrentDirectory(1024, Dir);
	if (isImage == true)
	{
		sprintf(imgStr, "\\%s.bmp", _vLoadItem[_currentGauge]->getImageResource().keyName.c_str());
		strcat(Dir, imgStr);
	}
	if (isImage == false)
	{
		sprintf(soundStr, "\\%s.mp3", _vLoadItem[_currentGauge]->getSoundResource().keyName.c_str());
		strcat(Dir, soundStr);
	}


	//��������� ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return FALSE;
}
void loading::fileNameText()
{
	//HFONT myfont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "THE����ڳ���M");
	//SelectObject(getMemDC(), myfont);
	//SetTextColor(getMemDC(), RGB(0, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), 55, _loadingBar->getRect().top + 2, Dir, strlen(Dir));
	//TextOut(getMemDC(), 55, _loadingBar->getRect().top + 2, Dir, strlen(Dir));
	//DeleteObject(myfont);
}
