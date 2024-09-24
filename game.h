#pragma once
#include "scene.h"
class Game :public Scene {
private:
	int _count =0;
public:
	void Init()override;
	void Update()override;
};