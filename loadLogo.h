#pragma once
#include "Polygon2D.h"
class LoadLogo :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\oruga_Z001.png"); }
	void Update();
};