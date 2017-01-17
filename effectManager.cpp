#include "stdafx.h"
#include "effectManager.h"

//����Ʈ �߰�
//����Ʈ�� �׸� ��ġ�� �Բ��׸� �̹����� Ű���� �޾ƿ;��Ѵ�
void effectManager::addEffect(float x, float y, char* effectImageKey)
{
	//����Ʈ�� �߰��Ѵ�
	tagEffect newEffect;
	newEffect._effectImg = IMAGEMANAGER->findImage(effectImageKey);
	//�̹����� �����̶� �ٽ� �������� ���� �־���Ѵ�
	newEffect._currentFrameX = 0;
	newEffect._x = x;
	newEffect._y = y;
	newEffect._width = newEffect._effectImg->getFrameWidth();
	newEffect._height = newEffect._effectImg->getFrameHeight();
	newEffect._rc = RectMakeCenter(newEffect._x, newEffect._y, newEffect._width, newEffect._height);
	newEffect._count = 0;

	_vEffect.push_back(newEffect);
}

//����Ʈ �׸���
void effectManager::update()
{
	//����Ʈ�� ������ ��ŭ �׸���
	for (int i = 0; i < _vEffect.size(); i++)
	{
		//�� ����Ʈ�� ī��Ʈ�� ����
		_vEffect[i]._count++;
		//�ϳ��� ����Ʈ�� ī��Ʈ�� 5�� �Ǿ��� ��
		if (_vEffect[i]._count % 5 == 0)
		{
			//���� ������ �Ѱ��ش�
			_vEffect[i]._currentFrameX++;
			//�̶� ���� ���� ���� ���
			if (_vEffect[i]._currentFrameX >= _vEffect[i]._effectImg->getMaxFrameX())
			{
				//����Ʈ�� �����ش�
				_vEffect.erase(_vEffect.begin() + i);
			}
			//���� ���� ���� ���
			else
			{
				//ī��Ʈ�� 0���� �ؼ� ���� ���� �׸� �ð��� �ʱ�ȭ ���ش�
				_vEffect[i]._count = 0;
			}
		}
	}
}

void effectManager::render(HDC hdc)
{
	// ��� �̹��� �׸���
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]._effectImg->frameRender(hdc, _vEffect[i]._x, _vEffect[i]._y, _vEffect[i]._currentFrameX, 0);
	}
}