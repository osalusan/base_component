#pragma once
#include "billboard.h"
class Tree :public BillBoard {
private:

public:
	void Init()override { _pivot = 1; BillBoard::Init(); _TransForm->_Scale = { 5.0f,5.0f,5.0f }; };
	void LoadTexture()override { Load(L"asset\\texture\\Tree07_1K.png"); }
};