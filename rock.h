#pragma once
#include "actor.h"
class Rock : public Actor
{
private:
	void Init()override {
		m_Sharder = new Sharder(this); m_Sharder->m_Usesharder = 0;	m_TransForm->m_Scale = { 1.0f,1.0f,1.0f };
		Actor::Init();
	};
	void LoadModel()override {m_Model = new ModelRenderer(this);m_Model->Init();m_Model->Load("asset\\model\\rock.obj");}
};