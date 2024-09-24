#pragma once
#include "skydome.h"
class Title_SkyDome :public SkyDome {
public:
	//void LoadTextureSkyDome()override {
	//	_ModelRenderer->LoadTexture("asset\\model\\snowy_forest.jpg");
	//}
	void LoadSkyDome()override { _ModelRenderer->Load("asset\\model\\sky.obj"); };
	void Update()override {};
};