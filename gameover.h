#pragma once
#include "scene.h"
class GameOver :public Scene {
private:
	int _select = 0;
public:
	void Init()override;
	void Update()override;
};