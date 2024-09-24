#pragma once
#include "scene.h"
class GameClear :public Scene {
private:
	int _select = 0;
public:
	void Init()override;
	void Update()override;
};