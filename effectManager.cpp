#include "stdafx.h"
#include "effectManager.h"

//이펙트 추가
//이펙트를 그릴 위치와 함께그릴 이미지의 키값을 받아와야한다
void effectManager::addEffect(float x, float y, char* effectImageKey)
{
	//이펙트를 추가한다
	tagEffect newEffect;
	newEffect._effectImg = IMAGEMANAGER->findImage(effectImageKey);
	//이미지가 한장이라 다시 프레임을 맞춰 주어야한다
	newEffect._currentFrameX = 0;
	newEffect._x = x;
	newEffect._y = y;
	newEffect._width = newEffect._effectImg->getFrameWidth();
	newEffect._height = newEffect._effectImg->getFrameHeight();
	newEffect._rc = RectMakeCenter(newEffect._x, newEffect._y, newEffect._width, newEffect._height);
	newEffect._count = 0;

	_vEffect.push_back(newEffect);
}

//이펙트 그리기
void effectManager::update()
{
	//이펙트의 사이즈 만큼 그린다
	for (int i = 0; i < _vEffect.size(); i++)
	{
		//각 이펙트의 카운트를 증가
		_vEffect[i]._count++;
		//하나의 이펙트의 카운트가 5가 되었을 때
		if (_vEffect[i]._count % 5 == 0)
		{
			//다음 장으로 넘겨준다
			_vEffect[i]._currentFrameX++;
			//이때 다음 장이 없을 경우
			if (_vEffect[i]._currentFrameX >= _vEffect[i]._effectImg->getMaxFrameX())
			{
				//이펙트를 지워준다
				_vEffect.erase(_vEffect.begin() + i);
			}
			//다음 장이 있을 경우
			else
			{
				//카운트를 0으로 해서 다음 장을 그릴 시간을 초기화 해준다
				_vEffect[i]._count = 0;
			}
		}
	}
}

void effectManager::render(HDC hdc)
{
	// 모든 이미지 그리기
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]._effectImg->frameRender(hdc, _vEffect[i]._x, _vEffect[i]._y, _vEffect[i]._currentFrameX, 0);
	}
}