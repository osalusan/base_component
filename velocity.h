#pragma once
#include "component.h"

class Velocity :public Component
{
public:
	
public:
	XMFLOAT3 _Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	using Component::Component;

	void Init()override {};
	void Unit()override {};
	void Update()override {};
	void Draw()override {};
};