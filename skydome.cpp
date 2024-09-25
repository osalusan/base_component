#include "skydome.h"
#include "manager.h"
#include "player.h"

void SkyDome::Init()
{
	m_Sharder = new Sharder(this);
	m_ModelRenderer = new ModelRenderer(this);
	m_TransForm->_Position = { 0.0f,0.0f,0.0f };
	m_TransForm->_Scale = { 500.0f,500.0f,500.0f };
	m_TransForm->_Rotation = { 0.0f,0.0f,0.0f };
	InitComponents();
	LoadTextureSkyDome();
	LoadSkyDome();

}

void SkyDome::Uninit()
{
	RemoveComponents();
}

void SkyDome::Update()
{
	m_TransForm->_Position = Manager::GetScene()->GetPlayerCharcter()->m_TransForm->_Position;
	UpdateComponents();
}

void SkyDome::Draw()
{
	//ワールドマトリクス設定
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(m_TransForm->_Scale.x, m_TransForm->_Scale.y, m_TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->_Rotation.x, m_TransForm->_Rotation.y, m_TransForm->_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->_Position.x, m_TransForm->_Position.y, m_TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	DrawComponents();
}

void SkyDome::InitComponents()
{
	m_Sharder->Init();
	m_ModelRenderer->Init();
}

void SkyDome::UpdateComponents()
{
	m_Sharder->Update();
	m_ModelRenderer->Update();
}

void SkyDome::DrawComponents()
{
	m_Sharder->Draw();
	m_ModelRenderer->Draw();
}

void SkyDome::RemoveComponents()
{
	if (m_Sharder != nullptr)m_Sharder->Unit(); delete m_Sharder;
	if (m_ModelRenderer != nullptr)m_ModelRenderer->Unit(); delete m_ModelRenderer;
}

void SkyDome::LoadSkyDome()
{
	m_ModelRenderer->Load("asset\\model\\sky.obj");
}

void SkyDome::LoadTextureSkyDome()
{
	//m_ModelRenderer->LoadTexture("asset\\model\\partly_cloudy_puresky.jpg");
}
