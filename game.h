#pragma once
#include "scene.h"
class Game :public Scene {
private:
	int m_Count =0;
	static bool m_LoadFinish;
public:
	void Init()override;
	void Update()override;
	void Uninit()override;
	static void Load();
	static bool GetLoadFinish() { return m_LoadFinish; }
};