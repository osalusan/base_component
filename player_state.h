#pragma once
#include "Polygon2D.h"
class Player;
class Player_Hp :public Polygon2D {
private:
	Player* _player;
	float _maxhp = 0;
public:
	using Polygon2D::Polygon2D;
	void Init()override;
	void Update()override;
	void Draw()override;
	void LoadTexture()override;
};
class Player_HpFrame :public Polygon2D {
private:

public:
	using Polygon2D::Polygon2D;
	void Init()override;
	void LoadTexture()override;
};
class Player_Stamina :public Polygon2D {
private:
	Player* _player;
	float _maxstamina = 0;
public:
	using Polygon2D::Polygon2D;
	void Init()override;
	void Update()override;
	void Draw()override;
	void LoadTexture()override;
};