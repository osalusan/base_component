#pragma once
#include "gameobj.h"
#include "sharder.h"
class BillBoard :public GameObject
{
protected:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader = {};
	ID3D11PixelShader* m_PixelShader = {};
	ID3D11InputLayout* m_VertexLayout = {};

	XMFLOAT3 _position = {};

	VERTEX_3D vertex[4];

	// スプライトシートの画像枚数
	XMINT2 _sprite = {};
	int m_Count = 0;
	unsigned int _animecount = 0;
	int _maxcount = 0;
	XMFLOAT2 _texTop = { 0.0f,0.0f };
	int _pivot = 0;
public:
	//using Component::Component;
	// インスタンス化の時に呼ぶ
	void SetBillBoard(XMFLOAT3 position, XMFLOAT3 size) { _position = position; _TransForm->_Scale = size; };
	void SetAnimation(int maxX, int maxY, int maxT) { _sprite.x = maxX; _sprite.y = maxY; _maxcount = maxT; }
	void SetBillBoardAnimation(XMFLOAT3 position, XMFLOAT3 size, int maxX, int maxY, int maxT) { _position = position; _TransForm->_Scale = size; _sprite.x = maxX; _sprite.y = maxY; _maxcount = maxT; }

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override {};
	virtual void UpdateComponent()override {};
	virtual void DrawComponent()override {};
	virtual void RemoveComponent()override {};
	virtual void SetSize(XMFLOAT3 size);
	virtual void Load(const wchar_t* FileName);
	virtual void LoadTexture();
	//描画のパターンを決める
};