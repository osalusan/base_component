#pragma once
#include "gameobj.h"
#include "sharder.h"
class Polygon2D:public GameObject
{
protected:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	//�R���|�[�l���g
	Sharder* m_Sharder{};

	VERTEX_3D m_Vertex[4]{};
	XMFLOAT4 m_Color = {1.0f,1.0f,1.0f,1.0f};
public:
	Polygon2D() {}
	Polygon2D(XMFLOAT3 position, XMFLOAT3 size,int pivot);
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	virtual void Load(const wchar_t* FileName);
	virtual void SetSize(XMFLOAT3 pos, XMFLOAT3 size, int pivot);
	virtual void LoadTexture();
	//�`��̃p�^�[�������߂�
};