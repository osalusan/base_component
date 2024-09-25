#pragma once
#include "billboard.h"
class Grass :public BillBoard {
private:

public:
	void Init()override { _pivot = 1; BillBoard::Init(); _TransForm->_Scale = { 2.0f,2.0f,2.0f }; };
	void LoadTexture()override { Load(L"asset\\texture\\Tree04_2K.png"); }
};