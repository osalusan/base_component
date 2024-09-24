#pragma once
#include "actor.h"
class FirePillar : public Actor
{
private:
	void Init()override;
	void LoadModel()override {
		_Model = new ModelRenderer(this);
		_Model->Init();
		_Model->Load("asset\\model\\fire_pillar.obj");
	}
};