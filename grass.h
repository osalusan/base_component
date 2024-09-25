#pragma once
#include "billboard.h"
class Grass :public BillBoard {
private:

public:
	void Init()override { m_Pivot = 1; BillBoard::Init(); m_TransForm->_Scale = { 2.0f,2.0f,2.0f }; };
	void LoadTexture()override { Load(L"asset\\texture\\Tree04_2K.png"); }
};