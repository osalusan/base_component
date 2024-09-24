
#include "actor.h"


void Actor::Init()
{
	// components

	InitComponent();
}

void Actor::Uninit()
{

	// components
	RemoveComponent();

}

void Actor::Update()
{

	// 移動
	Move();

	// 座標の設定
	_TransForm->_Position.x += _Velocity->_Velocity.x;
	_TransForm->_Position.y += _Velocity->_Velocity.y;
	_TransForm->_Position.z += _Velocity->_Velocity.z;

	// 当たり判定処理
	CollisionControl();

	UpdateComponent();
}

void Actor::Draw()
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
void Actor::InitComponent()
{
	_Velocity = new Velocity(this);
	_Sharder = new Sharder(this);
	_Velocity->Init();
	_Sharder->Init();
	LoadModel();
}


void Actor::UpdateComponent()
{
	if (_Velocity) { _Velocity->Update(); };
	if (_Sharder) { _Sharder->Update(); }
	if (_Model) { _Model->Update(); }
}

void Actor::DrawComponent()
{
	if (_AnimeModel) { _AnimeModel->Draw(); }
	if (_Model) { _Model->Draw(); }
	if (_Sharder) { _Sharder->Draw(); }
}

void Actor::RemoveComponent()
{
	if (_AnimeModel != nullptr)_AnimeModel->Unit(); delete _AnimeModel;
	if (_Model != nullptr)_Model->Unit(); delete _Model;
	if (_Sharder != nullptr)_Sharder->Unit(); delete _Sharder;
	if (_Velocity != nullptr) _Velocity->Unit(); delete _Velocity;
}

Actor::~Actor()
{

}

void Actor::LoadModel()
{
	//_Model = new ModelRenderer(this);
	//_Model->Init();
	//_Model->Load("asset\\model\\player.obj"); 

	//_AnimeModel = new AnimationModel(this);
	//_AnimeModel->Init();
	//_AnimeModel->Load("asset\\model\\Akai.fbx");
}

void Actor::CollisionControl()
{

}
