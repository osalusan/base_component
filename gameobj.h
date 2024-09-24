#pragma once
#include "main.h"
#include "renderer.h"
#include <map>
#include <list>
#include "scene.h"
#include "TransForm.h"

class GameObject {
public:
	TransForm* _TransForm = new TransForm(this);
	//���ʗpID/�R���|�[�l���g�ȂǂŎg��
	int ObjectID = 0;

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void InitComponent() = 0;
	virtual void UpdateComponent() = 0;
	virtual void DrawComponent() = 0;
	virtual void RemoveComponent() = 0;
	virtual ~GameObject() { delete _TransForm; _TransForm = nullptr; }
	virtual void NotifyAll() {}
	//��ꂽ�����ĂȂ���
	bool _Destroy = false;
	//����Ƃ��Ă�
	void SetDestroy() { _Destroy = true; }

	//�����_���Ŏg���p
	bool Destroy() {
		if (_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		return false;
	}
};