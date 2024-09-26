#pragma once
#include "gameobj.h"
#include "sharder.h"
class BillBoard :public GameObject
{
protected:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	XMFLOAT3 mm_Position = {};

	VERTEX_3D m_Vertex[4];
	Sharder* m_Sharder = nullptr;
	// スプライトシートの画像枚数
	XMINT2 m_Sprite = {};
	int m_Count = 0;
	unsigned int m_Animecount = 0;
	int m_Maxcount = 0;
	XMFLOAT2 m_TexTop = { 0.0f,0.0f };
	int m_Pivot = 0;
public:
	//using Component::Component;
	// インスタンス化の時に呼ぶ
	void SetBillBoard(XMFLOAT3 position, XMFLOAT3 size) { mm_Position = position; m_TransForm->m_Scale = size; };
	void SetAnimation(int maxX, int maxY, int maxT) { m_Sprite.x = maxX; m_Sprite.y = maxY; m_Maxcount = maxT; }
	void SetBillBoardAnimation(XMFLOAT3 position, XMFLOAT3 size, int maxX, int maxY, int maxT) { mm_Position = position; m_TransForm->m_Scale = size; m_Sprite.x = maxX; m_Sprite.y = maxY; m_Maxcount = maxT; }

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override {};
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	virtual void SetSize(XMFLOAT3 size);
	virtual void Load(const wchar_t* FileName);
	virtual void LoadTexture();
	//描画のパターンを決める
};