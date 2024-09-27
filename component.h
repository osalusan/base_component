#pragma once
#include "main.h"
#include <typeinfo>

class Component {
protected:
	class GameObject* _GameObject = nullptr;

public:
	Component() = delete;
	Component(GameObject* object) {
		_GameObject = object;
	}
	virtual ~Component() { _GameObject = nullptr; }

	virtual void Init() {};
	virtual void Unit() {};
	virtual void Update() {};
	virtual void Draw() {};

	
};
