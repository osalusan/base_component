#pragma once
#include "gameobj.h"
#include "sharder.h"
#define FILED_MAX (31)

class MeshFiled : public GameObject
{
private:


	ID3D11Buffer* _vertexBuffer = NULL;
	ID3D11Buffer* _indexBuffer =  NULL;
	ID3D11ShaderResourceView* _texture = NULL;
	ID3D11ShaderResourceView* _normal = NULL;

	Sharder* m_Sharder = {};

	VERTEX_3D m_Vertex[FILED_MAX][FILED_MAX]{};

	LIGHT light;
public:
	MeshFiled() {};
	~MeshFiled()override {};
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	float GetHeight(XMFLOAT3 position);
	void Load(const wchar_t* FileName, ID3D11ShaderResourceView*& texture);
};