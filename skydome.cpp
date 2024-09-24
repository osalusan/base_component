#include "skydome.h"
#include "manager.h"
#include "player.h"

void SkyDome::Init()
{
	_Sharder = new Sharder(this);
	_ModelRenderer = new ModelRenderer(this);
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
	_Sharder->Init();
	_ModelRenderer->Init();
}

void SkyDome::UpdateComponent()
{
	_Sharder->Update();
	_ModelRenderer->Update();
}

void SkyDome::DrawComponent()
{
	_Sharder->Draw();
	_ModelRenderer->Draw();
}

void SkyDome::RemoveComponent()
{
	if (_Sharder != nullptr)_Sharder->Unit(); delete _Sharder;
	if (_ModelRenderer != nullptr)_ModelRenderer->Unit(); delete _ModelRenderer;
}

void SkyDome::LoadSkyDome()
{
	_ModelRenderer->Load("asset\\model\\sky.obj");
}

void SkyDome::LoadTextureSkyDome()
{
	//_ModelRenderer->LoadTexture("asset\\model\\partly_cloudy_puresky.jpg");
}
