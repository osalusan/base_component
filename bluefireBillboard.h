#pragma once
#include "billboard.h"
class BlueFire_BillBoard : public BillBoard {
private:

public:
	void LoadTexture()override {
		Load(L"asset\\texture\\T_bluefire.png"); SetAnimation(3,1,6);
	};
};