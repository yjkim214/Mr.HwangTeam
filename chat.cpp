#include "stdafx.h"
#include "chat.h"

HRESULT chat::init(void)
{
	_x = 100;
	_y = 400;
	_count = 0;
	return S_OK;
}

void chat::release(void)
{
}

void chat::update(void)
{
}

void chat::render(void)
{
	IMAGEMANAGER->render("chat", getMemDC(), _x, _y);
}

void chat::AlthenaChat()
{
	IMAGEMANAGER->render("Althena", getMemDC(), 300, 110);
	IMAGEMANAGER->render("AlthenaText", getMemDC(), _x + 30, _y + 30);

	if (_count >= 1)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "��", strlen("��"));
	}
	if (_count >= 20)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "���", strlen("���"));
	}
	if (_count >= 40)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "�����", strlen("�����"));
	}
	if (_count >= 60)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ", strlen("����� "));
	}
	if (_count >= 80)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ��", strlen("����� ��"));
	}
	if (_count >= 100)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ����", strlen("����� ����"));
	}
	if (_count >= 120)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������", strlen("����� ������"));
	}
	if (_count >= 140)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ", strlen("����� ������ "));
	}
	if (_count >= 160)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ��", strlen("����� ������ ��"));
	}
	if (_count >= 180)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ����", strlen("����� ������ ����"));
	}
	if (_count >= 200)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ���ڽ�", strlen("����� ������ ���ڽ�"));
	}
	if (_count >= 220)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ���ڽ���", strlen("����� ������ ���ڽ���"));
	}
	if (_count >= 240)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ���ڽ��ϴ�", strlen("����� ������ ���ڽ��ϴ�"));
	}
	if (_count >= 260)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "����� ������ ���ڽ��ϴ�.", strlen("����� ������ ���ڽ��ϴ�."));
	}
}

void chat::kidsChat()
{
	if (_count >= 1)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "��", strlen("��"));
	}
	if (_count >= 20)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;�", strlen("�;�"));
	}
	if (_count >= 40)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;ƾ�", strlen("�;ƾ�"));
	}
	if (_count >= 60)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;ƾƾ�", strlen("�;ƾƾ�"));
	}
	if (_count >= 80)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;ƾƾƾ�", strlen("�;ƾƾƾ�"));
	}
	if (_count >= 100)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;ƾƾƾ�~", strlen("�;ƾƾƾ�~"));
	}
	if (_count >= 120)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "�;ƾƾƾ�~~", strlen("�;ƾƾƾ�~~"));
	}
}

void chat::misterChat()
{
	TextOut(getMemDC(), _x + 100, _y + 95, "������.", strlen("������."));
}
