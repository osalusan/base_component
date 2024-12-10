#include "component.h"
#include "main.h"
#include "renderer.h"
#include "Polygon2D.h"
#include "texturecacheManager.h"

//-------------------------------------------
//原点
// 0:中央　1:左上　2:右上　3:左下　4:右下
//-------------------------------------------
Polygon2D::Polygon2D(XMFLOAT3 position, XMFLOAT3 size,int pivot)
{

	if (pivot < 0 && pivot > 4)return;
	m_TransForm->m_Position = position;
	m_TransForm->m_Scale = size;
	if (pivot == 0)
	{// 中央
		m_Vertex[0].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 1)
	{// 左上
		m_Vertex[0].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x, position.y + size.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + size.x, position.y + size.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 2)
	{// 右上
		m_Vertex[0].Position = XMFLOAT3(position.x - size.x, position.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - size.x, position.y + size.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x, position.y + size.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 3)
	{//左下
		m_Vertex[0].Position = XMFLOAT3(position.x, position.y - size.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + size.x, position.y - size.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 4)
	{// 右下
		m_Vertex[0].Position = XMFLOAT3(position.x - size.x, position.y - size.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x, position.y - size.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - size.x, position.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}

}

void Polygon2D::Init()
{

	LoadTexture();


	//頂点バッファの生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_Vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	InitComponents();
}

void Polygon2D::Uninit()
{
	RemoveComponents();

	m_VertexBuffer->Release();
	m_Texture->Release();
}

void Polygon2D::Update()
{
	UpdateComponents();
}

void Polygon2D::Draw()
{
	DrawComponents();

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	XMMATRIX world, scl, rot, trans;

	scl = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x, m_TransForm->m_Position.y, m_TransForm->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	//頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = m_Color;
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Polygon2D::InitComponents()
{
	m_Sharder = new Sharder(this);
	m_Sharder->Init();
}

void Polygon2D::UpdateComponents()
{
	m_Sharder->Update();
}

void Polygon2D::DrawComponents()
{
	m_Sharder->Draw();
}

void Polygon2D::RemoveComponents()
{
	m_Sharder->Unit();
	delete m_Sharder;
}

void Polygon2D::Load(const wchar_t* FileName)
{
	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;

	TextureCacheManager::LoadTexture(FileName, metadata, image, m_Texture);
	assert(m_Texture);

}

void Polygon2D::SetSize(XMFLOAT3 position, XMFLOAT3 size, int pivot)
{
	if (pivot < 0 && pivot > 4)return;


	m_TransForm->m_Position = position;
	m_TransForm->m_Scale = size;

	position = { 0.0f,0.0f,0.0f };
	size = { 1.0f,1.0f,0.0f };
	if (pivot == 0)
	{// 中央
		m_Vertex[0].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y - (size.y * 0.5f), 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + (size.x * 0.5f), position.y + (size.y * 0.5f), 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 1)
	{// 左上
		m_Vertex[0].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x, position.y + size.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + size.x, position.y + size.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 2)
	{// 右上
		m_Vertex[0].Position = XMFLOAT3(position.x - size.x, position.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - size.x, position.y + size.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x, position.y + size.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 3)
	{//左下
		m_Vertex[0].Position = XMFLOAT3(position.x, position.y - size.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x + size.x, position.y - size.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
	else if (pivot == 4)
	{// 右下
		m_Vertex[0].Position = XMFLOAT3(position.x - size.x, position.y - size.y, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		m_Vertex[1].Position = XMFLOAT3(position.x, position.y - size.y, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		m_Vertex[2].Position = XMFLOAT3(position.x - size.x, position.y, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(position.x, position.y, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		return;
	}
}

void Polygon2D::LoadTexture()
{
	Load(L"asset\\texture\\oruga_T001.png");
}

