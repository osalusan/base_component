#pragma once
#include "billboard.h"
class Grass :public BillBoard {
private:
	ID3D11Buffer* m_PositionBuffer{};
	ID3D11ShaderResourceView* m_PositionSRV{};
public:
	void Init()override;
	void Uninit()override;
	void Draw()override;
	void LoadTexture()override { Load(L"asset\\texture\\Grass-4.png"); }
};