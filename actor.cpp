
#include "actor.h"


void Actor::Init()
{
	// components

	InitComponents();
}

void Actor::Uninit()
{

	// components
	RemoveComponents();

}

void Actor::Update()
{

	// 移動
	Move();

	// 座標の設定
	m_TransForm->m_Position.x += m_Velocity->m_Velocity.x;
	m_TransForm->m_Position.y += m_Velocity->m_Velocity.y;
	m_TransForm->m_Position.z += m_Velocity->m_Velocity.z;

	// 当たり判定処理
	CollisionControl();

	UpdateComponents();
}

void Actor::Draw()
{
	DrawComponents();
	//ワールドマトリクス設定
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x, m_TransForm->m_Position.y, m_TransForm->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);
}
void Actor::InitComponents()
{
	m_Velocity = new Velocity(this);
	if (!m_Sharder) { m_Sharder = new Sharder(this); }
	m_Velocity->Init();
	m_Sharder->Init();
	LoadModel();
}


void Actor::UpdateComponents()
{
	 m_Velocity->Update();
	 m_Sharder->Update(); 
	if (m_Model) { m_Model->Update(); }
}

void Actor::DrawComponents()
{
	if (m_AnimeModel) { m_AnimeModel->Draw(); }
	if (m_Model) { m_Model->Draw(); }
	 m_Sharder->Draw();
}

void Actor::RemoveComponents()
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
