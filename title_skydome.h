#pragma once
#include "skydome.h"
class Title_SkyDome :public SkyDome {
public:
	//void LoadTextureSkyDome()override {
	//	m_ModelRenderer->LoadTexture("asset\\model\\snowy_forest.jpg");
	//}
	void LoadSkyDome()override { m_ModelRenderer->Load("asset\\model\\sky.obj"); };
	void Update()override {};
};