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
		TextOut(getMemDC(), _x + 100, _y + 110, "당", strlen("당"));
	}
	if (_count >= 20)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신", strlen("당신"));
	}
	if (_count >= 40)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의", strlen("당신의"));
	}
	if (_count >= 60)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 ", strlen("당신의 "));
	}
	if (_count >= 80)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무", strlen("당신의 무"));
	}
	if (_count >= 100)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운", strlen("당신의 무운"));
	}
	if (_count >= 120)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을", strlen("당신의 무운을"));
	}
	if (_count >= 140)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 ", strlen("당신의 무운을 "));
	}
	if (_count >= 160)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌", strlen("당신의 무운을 빌"));
	}
	if (_count >= 180)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌겠", strlen("당신의 무운을 빌겠"));
	}
	if (_count >= 200)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌겠습", strlen("당신의 무운을 빌겠습"));
	}
	if (_count >= 220)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌겠습니", strlen("당신의 무운을 빌겠습니"));
	}
	if (_count >= 240)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌겠습니다", strlen("당신의 무운을 빌겠습니다"));
	}
	if (_count >= 260)
	{
		TextOut(getMemDC(), _x + 100, _y + 110, "당신의 무운을 빌겠습니다.", strlen("당신의 무운을 빌겠습니다."));
	}
}

void chat::kidsChat()
{
	if (_count >= 1)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와", strlen("와"));
	}
	if (_count >= 20)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아", strlen("와아"));
	}
	if (_count >= 40)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아아", strlen("와아아"));
	}
	if (_count >= 60)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아아아", strlen("와아아아"));
	}
	if (_count >= 80)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아아아아", strlen("와아아아아"));
	}
	if (_count >= 100)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아아아아~", strlen("와아아아아~"));
	}
	if (_count >= 120)
	{
		TextOut(getMemDC(), _x + 100, _y + 95, "와아아아아~~", strlen("와아아아아~~"));
	}
}

void chat::misterChat()
{
	TextOut(getMemDC(), _x + 100, _y + 95, "……….", strlen("………."));
}
