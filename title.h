#pragma once

class Title :public Scene {
private:
	int stage = 0;
public:
	void Init()override;
	void Update()override;
};
