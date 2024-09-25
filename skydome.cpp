#include "skydome.h"
#include "manager.h"
#include "player.h"

void SkyDome::Init()
{
	m_Sharder = new Sharder(this);
	m_ModelRenderer = new ModelRenderer(this);
	_TransForm->_Position = { 0.0f,0.0f,0.0f };
	_TransForm->_Scale = { 500.0f,500.0f,500.0f };
	_TransForm->_Rotation = { 0.0f,0.0f,0.0f };
	InitComponent();
	LoadTextureSkyDome();
	LoadSkyDome();

}

void SkyDome::Uninit()
{
	RemoveComponent();
}

void SkyDome::Update()
{
	_TransForm->_Position = Manager::GetScene()->GetPlayerCharcter()->_TransForm->_Position;
	UpdateComponent();
}

void SkyDome::Draw()
{
	//ワールドマトリクス設定
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x, _TransForm->_Position.y, _TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	DrawComponent();
}

void SkyDome::InitComponent()
{
	m_Sharder->Init();
	m_ModelRenderer->Init();
}

void SkyDome::UpdateComponent()
{
	m_Sharder->Update();
	m_ModelRenderer->Update();
}

void SkyDome::DrawComponent()
{
	m_Sharder->Draw();
	m_ModelRenderer->Draw();
}

void SkyDome::RemoveComponent()
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
