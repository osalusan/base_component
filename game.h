#pragma once
#include "scene.h"
class Game :public Scene {
private:
	int m_Count =0;
public:
	void Init()override;
	void Update()override;
};