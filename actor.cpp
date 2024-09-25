
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

	// �ړ�
	Move();

	// ���W�̐ݒ�
	m_TransForm->_Position.x += m_Velocity->m_Velocity.x;
	m_TransForm->_Position.y += m_Velocity->m_Velocity.y;
	m_TransForm->_Position.z += m_Velocity->m_Velocity.z;

	// �����蔻�菈��
	CollisionControl();

	UpdateComponents();
}

void Actor::Draw()
{
	DrawComponents();
	//���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(m_TransForm->_Scale.x, m_TransForm->_Scale.y, m_TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->_Rotation.x, m_TransForm->_Rotation.y, m_TransForm->_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->_Position.x, m_TransForm->_Position.y, m_TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);
}
void Actor::InitComponents()
{
	m_Velocity = new Velocity(this);
	m_Sharder = new Sharder(this);
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
