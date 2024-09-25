#pragma once
#include "gameobj.h"
#include "sharder.h"
#define FILED_MAX (31)

class MeshFiled : public GameObject
{
private:


	ID3D11Buffer* _vertexBuffer = NULL;
	ID3D11Buffer* _indexBuffer =  NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_Normal = NULL;

	Sharder* m_Sharder = {};

	VERTEX_3D m_Vertex[FILED_MAX][FILED_MAX]{};

	LIGHT m_Light;
public:
	MeshFiled() {};
	~MeshFiled()override {};
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	float GetHeight(XMFLOAT3 position);
	void Load(const wchar_t* FileName, ID3D11ShaderResourceView*& texture);
};