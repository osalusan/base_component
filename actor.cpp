
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
	_TransForm->_Position.x += m_Velocity->m_Velocity.x;
	_TransForm->_Position.y += m_Velocity->m_Velocity.y;
	_TransForm->_Position.z += m_Velocity->m_Velocity.z;

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
	m_Velocity = new Velocity(this);
	m_Sharder = new Sharder(this);
	m_Velocity->Init();
	m_Sharder->Init();
	LoadModel();
}


void Actor::UpdateComponent()
{
	 m_Velocity->Update();
	 m_Sharder->Update(); 
	if (m_Model) { m_Model->Update(); }
}

void Actor::DrawComponent()
{
	if (m_AnimeModel) { m_AnimeModel->Draw(); }
	if (m_Model) { m_Model->Draw(); }
	 m_Sharder->Draw();
}

void Actor::RemoveComponent()
{
	if (m_AnimeModel != nullptr)m_AnimeModel->Unit(); delete m_AnimeModel;
	if (m_Model != nullptr)m_Model->Unit(); delete m_Model;
	m_Sharder->Unit(); delete m_Sharder;
	m_Velocity->Unit(); delete m_Velocity;
}

Actor::~Actor()
{

}

void Actor::LoadModel()
{
	//m_Model = new ModelRenderer(this);
	//m_Model->Init();
	//m_Model->Load("asset\\model\\player.obj"); 

	//m_AnimeModel = new AnimationModel(this);
	//m_AnimeModel->Init();
	//m_AnimeModel->Load("asset\\model\\Akai.fbx");
}

void Actor::CollisionControl()
{

}
