#include "billboard.h"
#include "player_camera.h"
#include "manager.h"
#include "texturecacheManager.h"


ID3D11ShaderResourceView* BillBoard::m_Texture = nullptr;

void BillBoard::Init()
{
	LoadTexture();

	if (m_Pivot == 0)
	{// 中央が原点
		m_Vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f + m_TexTop.y);

		m_Vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f + m_TexTop.y);

		m_Vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}
	else if (m_Pivot == 1)
	{// 中央下が原点
		m_Vertex[0].Position = XMFLOAT3(-1.0f, 2.0f, 0.0f);
		m_Vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f + m_TexTop.y);

		m_Vertex[1].Position = XMFLOAT3(1.0f, 2.0f, 0.0f);
		m_Vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f + m_TexTop.y);

		m_Vertex[2].Position = XMFLOAT3(-1.0f, 0.0f, 0.0f);
		m_Vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		m_Vertex[3].Position = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_Vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}

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

void BillBoard::Uninit()
{

	RemoveComponents();

	m_VertexBuffer->Release();
	m_Texture->Release();
}

void BillBoard::Update()
{
	if (m_Count >= m_Maxcount) { m_Animecount++; m_Count = 0; }
	if (m_Animecount >= 4094967295) { m_Animecount = 0; }
	m_Count++;
}

void BillBoard::Draw()
{
	DrawComponents();

	if (m_Sprite.x != 0)
	{
		//テクスチャ座標算出(剰余斬)
		float x = m_Animecount % m_Sprite.x * (1.0f / m_Sprite.x);
		float y = m_Animecount / m_Sprite.x * (1.0f / m_Sprite.y);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(x, y);

		vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(x + 0.25f, y);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(-1.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(x, y + (1.0f / m_Sprite.y));

		vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(x + (1.0f / m_Sprite.x), y + (1.0f / m_Sprite.y));

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	Player_Camera* camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMMATRIX view = camera->GetViewMatrix();

	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + m_Position.x,m_TransForm->m_Position.y + m_Position.y, m_TransForm->m_Position.z + m_Position.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(world);

	//頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	
	// アルファトゥカバレッジ有効
	Renderer::SetATCEnable(true);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetATCEnable(false);

}

void BillBoard::InitComponents()
{
	m_Sharder = new Sharder(this); m_Sharder->m_Usesharder = 0; m_Sharder->Init();
}

void BillBoard::DrawComponents()
{
	m_Sharder->Draw();
}

void BillBoard::RemoveComponents()
{
	m_Sharder->Unit(); delete m_Sharder;
}


void BillBoard::SetSize(XMFLOAT3 size)
{
	m_TransForm->m_Scale = size;
}

void BillBoard::Load(const wchar_t* FileName)
{
	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;

	TextureCacheManager::LoadTexture(FileName,metadata,image,m_Texture);
	assert(m_Texture);
}

void BillBoard::LoadTexture()
{

}
