#pragma once
#include "skydome.h"
class Game_SkyDome :public SkyDome {
public:
	void LoadSkyDome()override { _ModelRenderer->Load("asset\\model\\sky2.obj"); };
};