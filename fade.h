#pragma once
#include "gameobj.h"
#include "sharder.h"
class Fade
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = {};
	ID3D11PixelShader* m_PixelShader = {};
	ID3D11InputLayout* m_VertexLayout = {};

	VERTEX_3D vertex[4];

	int m_Count;

	float _time = 120.0f;
	float _udalfa = 0.0f;
public:
	float _alfa = 0.0f;
	bool _used;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Load(const wchar_t* FileName);
	void StartFadeIn();
	void StartFadeOut();
	//•`‰æ‚Ìƒpƒ^[ƒ“‚ğŒˆ‚ß‚é

};