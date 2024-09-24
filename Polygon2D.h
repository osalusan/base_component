#pragma once
#include "gameobj.h"
#include "sharder.h"
class Polygon2D:public GameObject
{
protected:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	//コンポーネント
	Sharder* _Sharder{};

	VERTEX_3D vertex[4]{};
	XMFLOAT4 _color = {1.0f,1.0f,1.0f,1.0f};
public:
	Polygon2D() {}
	Polygon2D(XMFLOAT3 position, XMFLOAT3 size,int pivot);
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	virtual void Load(const wchar_t* FileName);
	virtual void SetSize(XMFLOAT3 pos, XMFLOAT3 size, int pivot);
	virtual void LoadTexture();
	//描画のパターンを決める
};