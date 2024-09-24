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
	//識別用ID/コンポーネントなどで使う
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
	//壊れたか壊れてないか
	bool _Destroy = false;
	//壊れるとき呼ぶ
	void SetDestroy() { _Destroy = true; }

	//ラムダ式で使う用
	bool Destroy() {
		if (_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		return false;
	}
};