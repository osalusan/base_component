#pragma once
#include "Polygon2D.h"
//class Result_BackGround :public Polygon2D {
//public:
//	using Polygon2D::Polygon2D;
//	void LoadTexture() { Load(L"asset\\texture\\oruga_T001.png"); }
//};
class Result_BackTitle :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_goTitle.png"); }
};
class Result_Retry:public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_Retry.png"); }
};
class Result_Clear :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_GameClear.png"); }
};
class Result_Over :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_GameOver.png"); }
};

class Result_Select :public Polygon2D {
public:
	using Polygon2D::Polygon2D;
	void LoadTexture() { Load(L"asset\\texture\\T_black.png"); }
	void Draw()override {
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
		XMFLOAT3 position = m_TransForm->m_Position;
		XMFLOAT3 size = m_TransForm->m_Scale;

		vertex[0].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
		Polygon2D::Draw();
	};
};