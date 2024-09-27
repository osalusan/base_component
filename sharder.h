#pragma once
#include "renderer.h"
#include "component.h"
class Sharder : public Component
{
private:
	ID3D11VertexShader* m_VertexShader = {};
	ID3D11PixelShader* m_PixelShader = {};
	ID3D11InputLayout* m_VertexLayout = {};
public:
	int m_Usesharder = 0;
	using Component::Component;
	void Init()override;
	void Unit()override;
	void Draw()override;
};