#include "particleEmiter.h"
#include "manager.h"
#include "player_camera.h"


void ParticleEmiter::Init()
{
	LoadParticleTexture();

	InitComponents();
	VERTEX_3D vertex[4];


	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	//頂点バッファの生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		m_Particle[i].color = { 1.0f,1.0f,1.0f,1.0f };
	}
	m_Mix = true;

}

void ParticleEmiter::Uninit()
{
	RemoveComponents();
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void ParticleEmiter::Update()
{
	UpdateComponents();
	////パーティクルの発射
	//for (int i = 0; i < PARTICLE_MAX; i++)
	//{
	//	if (!m_Particle[i].Enable)
	//	{
	//		m_Particle[i].Enable = true;
	//		m_Particle[i].position = m_TransForm->_Position;
	//		m_Particle[i].velocity.x = (rand() % 100 - 50) * 0.003f;
	//		m_Particle[i].velocity.y = (rand() % 100 - 50) * 0.003f;
	//		m_Particle[i].velocity.z = (rand() % 100 - 50) * 0.003f;
	//		m_Particle[i].scale = m_TransForm->_Scale;
	//		m_Particle[i].lifetime = 220.0f;
	//		break;
	//	}
	//}
	////パーティクルの処理
	//for (int i = 0; i < PARTICLE_MAX; i++)
	//{
	//	if (m_Particle[i].Enable)
	//	{
	//		m_Particle[i].position.x += m_Particle[i].velocity.x;
	//		m_Particle[i].position.y += m_Particle[i].velocity.y;
	//		m_Particle[i].position.z += m_Particle[i].velocity.z;

	//		m_Particle[i].lifetime--;
	//		if (m_Particle[i].lifetime <= 0)
	//		{
	//			m_Particle[i].Enable = false;
	//		}
	//	}
	//	
	//}
}

void ParticleEmiter::Draw()
{
	DrawComponents();

	Player_Camera* camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMMATRIX view = camera->GetViewMatrix();

	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	//頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Zバッファ無効
	Renderer::SetDepthEnable(false);
	//加算合成を有効
	if (m_Mix)Renderer::SetBlendAddEnable(true);



	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable)
		{
			//マテリアル設定
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = m_Particle[i].color;
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			//ワールドマトリクス設定
			XMMATRIX world, scale, rot, trans;
			scale = XMMatrixScaling(m_Particle[i].scale.x,m_Particle[i].scale.y,m_Particle[i].scale.z);
			trans = XMMatrixTranslation(m_Particle[i].position.x, m_Particle[i].position.y, m_Particle[i].position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			//ポリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	//Zバッファ有効
	Renderer::SetDepthEnable(true);

	//加算合成を無効
	if (m_Mix)Renderer::SetBlendAddEnable(false);

}

void ParticleEmiter::InitComponents()
{
	m_Sharder = new Sharder(this);

	m_Sharder->Init();
}

void ParticleEmiter::UpdateComponents()
{
	
}

void ParticleEmiter::DrawComponents()
{
	if (m_Sharder) { m_Sharder->Draw();}
}

void ParticleEmiter::RemoveComponents()
{
	if (m_Sharder) { m_Sharder->Unit(); delete m_Sharder; }
}

void ParticleEmiter::Load(const wchar_t* FileName)
{
	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(FileName, WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
}

void ParticleEmiter::LoadParticleTexture()
{
	Load(L"asset\\texture\\particleOrigin.png");
}
