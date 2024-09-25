#pragma once
#include "billboard.h"
class Tree :public BillBoard {
private:

public:
	void Init()override { m_Pivot = 1; BillBoard::Init(); float size = (rand() % 50) * 0.1f + 4.0f; m_TransForm->_Scale = { size,size,size }; };
	void LoadTexture()override { Load(L"asset\\texture\\Tree04_2K.png"); }
};