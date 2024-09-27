#pragma once
#include "actor.h"
class FirePillar : public Actor
{
private:
	void Init()override;
	void LoadModel()override {
		m_Model = new ModelRenderer(this);
		m_Model->Init();
		m_Model->Load("asset\\model\\fire_pillar.obj");
	}
};