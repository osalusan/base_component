#pragma once
#include "skydome.h"
class Game_SkyDome :public SkyDome {
public:
	void LoadSkyDome()override { m_ModelRenderer->Load("asset\\model\\sky2.obj"); };
};