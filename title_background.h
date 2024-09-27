#pragma once
#include "Polygon2D.h"
class Title_BackGround :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_seedum.png"); }
};
class Title_Enter : public Polygon2D {
private:
	bool _direction = false;
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_PushSpace.png"); }
	void Update() { 
		float ud = 0.015f;
		if (m_Color.w <= 0.15f) { _direction = false; }
		else if (m_Color.w >= 1.0f) { _direction = true; }
		if (_direction) { ud *= -1; }
		m_Color.w+= ud;
	};
};