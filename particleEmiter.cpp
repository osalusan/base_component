#include "particleEmiter.h"
#include "manager.h"
#include "player_camera.h"


void ParticleEmiter::Init()
{
	LoadParticleTexture();

	InitComponent();
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


	//���_�o�b�t�@�̐���
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
		_particle[i].color = { 1.0f,1.0f,1.0f,1.0f };
	}
	_mix = true;

}

void ParticleEmiter::Uninit()
{
	RemoveComponent();
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void ParticleEmiter::Update()
{
	UpdateComponent();
	////�p�[�e�B�N���̔���
	//for (int i = 0; i < PARTICLE_MAX; i++)
	//{
	//	if (!_particle[i].Enable)
	//	{
	//		_particle[i].Enable = true;
	//		_particle[i].position = _TransForm->_Position;
	//		_particle[i].velocity.x = (rand() % 100 - 50) * 0.003f;
	//		_particle[i].velocity.y = (rand() % 100 - 50) * 0.003f;
	//		_particle[i].velocity.z = (rand() % 100 - 50) * 0.003f;
	//		_particle[i].scale = _TransForm->_Scale;
	//		_particle[i].lifetime = 220.0f;
	//		break;
	//	}
	//}
	////�p�[�e�B�N���̏���
	//for (int i = 0; i < PARTICLE_MAX; i++)
	//{
	//	if (_particle[i].Enable)
	//	{
	//		_particle[i].position.x += _particle[i].velocity.x;
	//		_particle[i].position.y += _particle[i].velocity.y;
	//		_particle[i].position.z += _particle[i].velocity.z;

	//		_particle[i].lifetime--;
	//		if (_particle[i].lifetime <= 0)
	//		{
	//			_particle[i].Enable = false;
	//		}
	//	}
	//	
	//}
}

void ParticleEmiter::Draw()
{
	DrawComponent();

	Player_Camera* camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMMATRIX view = camera->GetViewMatrix();

	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//�t�s��
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	//���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Z�o�b�t�@����
	Renderer::SetDepthEnable(false);
	//���Z������L��
	if (_mix)Renderer::SetBlendAddEnable(true);



	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_particle[i].Enable)
		{
			//�}�e���A���ݒ�
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = _particle[i].color;
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			//���[���h�}�g���N�X�ݒ�
			XMMATRIX world, scale, rot, trans;
			scale = XMMatrixScaling(_particle[i].scale.x,_particle[i].scale.y,_particle[i].scale.z);
			trans = XMMatrixTranslation(_particle[i].position.x, _particle[i].position.y, _particle[i].position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			//�|���S���`��
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	//Z�o�b�t�@�L��
	Renderer::SetDepthEnable(true);

	//���Z�����𖳌�
	if (_mix)Renderer::SetBlendAddEnable(false);

}

void ParticleEmiter::InitComponent()
{
	_Sharder = new Sharder(this);

	_Sharder->Init();
}

void ParticleEmiter::UpdateComponent()
{
	
}

void ParticleEmiter::DrawComponent()
{
	if (_Sharder) { _Sharder->Draw();}
}

void ParticleEmiter::RemoveComponent()
{
	if (_Sharder) { _Sharder->Unit(); delete _Sharder; }
}

void ParticleEmiter::Load(const wchar_t* FileName)
{
	//�e�N�X�`���ǂݍ���
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
