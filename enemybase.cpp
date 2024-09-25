#include "enemybase.h"
#include "manager.h"
#include "result.h"
#include "gameclear.h"
EnemyBase::EnemyBase()
{
	
}

void EnemyBase::Init()
{
	// components
	InitComponent();
	SetState(ENEMY_STATE::Enemy_Idel);
	SetMaxPaturn();

}

void EnemyBase::Uninit()
{
	// components
	RemoveComponent();
}

void EnemyBase::Update()
{
	EnemyStateControl();
	StateControl();
	UpdateComponent();
	AnimationControl();

	//座標の設定
	_TransForm->_Position.x += m_Velocity->m_Velocity.x;
	_TransForm->_Position.y += m_Velocity->m_Velocity.y;
	_TransForm->_Position.z += m_Velocity->m_Velocity.z;

	m_Count++;
}

void EnemyBase::Draw()
{
	// ワールドマトリクス設定
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x, _TransForm->_Position.y, _TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);
	DrawComponent();
}

void EnemyBase::InitComponent()
{
	m_Velocity = new Velocity(this);
	m_Sharder = new Sharder(this);
	_Animation = new Animation(this);
	m_Velocity->Init();
	m_Sharder->Init();
	_Animation->Init();
	LoadModel();
}

void EnemyBase::UpdateComponent()
{

	if (m_Velocity) { m_Velocity->Update(); };
	if (m_Sharder) { m_Sharder->Update(); }
	if (m_Model) { m_Model->Update(); }
	if (_Animation) { _Animation->Update(); }

}

void EnemyBase::DrawComponent()
{
	if (_Animation) { _Animation->Draw(); }
	if (m_Model) { m_Model->Draw(); }
	if (_AnimModel) { _AnimModel->Draw(); }
	if (m_Sharder) { m_Sharder->Draw(); }
}

void EnemyBase::RemoveComponent()
{
	if (_AnimModel != nullptr)_AnimModel->Unit(); delete _AnimModel;
	if (_Animation != nullptr)_Animation->Unit(); delete _Animation;
	if (m_Model != nullptr)m_Model->Unit(); delete m_Model;
	if (m_Sharder != nullptr)m_Sharder->Unit(); delete m_Sharder;
	if (m_Velocity != nullptr) m_Velocity->Unit(); delete m_Velocity;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::EnemyAnimation()
{

}

void EnemyBase::EnemyStateControl()
{
	switch (_state)
	{
	case ENEMY_STATE::Enemy_Idel:
		StateIdel();
		break;
	case ENEMY_STATE::Enemy_Search:
		StateSearch();
		break;
	case ENEMY_STATE::Enemy_Move:
		StateMove();
		break;
	case ENEMY_STATE::Enemy_Attack:
		StateAttack();
		break;
	case ENEMY_STATE::Enemy_Stagger:
		StateStagger();
		break;
	case ENEMY_STATE::Enemy_Down:
		StateDown();
		break;
	default:
		break;
	}
}

void EnemyBase::SetState(ENEMY_STATE state)
{
	
	if (_state == state) return;
	if (!_player) { _player = Manager::GetScene()->GetGameObject<Player>(); }
	_state = state; m_Count = 0;

	if (_idleMax == 0)return;

	int randValue = rand();
	switch (_state)
	{
	case ENEMY_STATE::Enemy_Idel:
		_paturnNo = randValue% _idleMax;
		break;
	case ENEMY_STATE::Enemy_Search:
		SetState(state);
		break;
	case ENEMY_STATE::Enemy_Move:
		_paturnNo = randValue % _moveMax;
		break;
	case ENEMY_STATE::Enemy_Attack:
		_paturnNo = randValue % _atkMax;
		break;
	case ENEMY_STATE::Enemy_Stagger:
		SetState(state);
		break;
	case ENEMY_STATE::Enemy_Down:
		_paturnNo = randValue % _downMax;
		break;
	default:
		break;
	}
	m_Velocity->m_Velocity = { 0.0f,0.0f,0.0f };
}

void EnemyBase::SetRandState()
{
	m_Count = 0;
	int select = rand() % 2;
	switch (select)
	{
	case 0:
		_state = ENEMY_STATE::Enemy_Move;
		break;
	case 1:
		_state = ENEMY_STATE::Enemy_Attack;
		break;
	default:
		break;
	}
	int randValue = rand();

	switch (_state)
	{
	case ENEMY_STATE::Enemy_Idel:
		SetRandState();
		break;
	case ENEMY_STATE::Enemy_Search:
		SetRandState();
		break;
	case ENEMY_STATE::Enemy_Move:
		_paturnNo = randValue % _moveMax;
		break;
	case ENEMY_STATE::Enemy_Attack:
		_paturnNo = randValue % _atkMax;
		break;
	case ENEMY_STATE::Enemy_Stagger:
		SetRandState();
		break;
	case ENEMY_STATE::Enemy_Down:
		SetRandState();
		break;
	default:
		SetRandState();
		break;
	}
	m_Velocity->m_Velocity = { 0.0f,0.0f,0.0f };

}

void EnemyBase::SetDebugState(ENEMY_STATE state, int paturn)
{
	if (_state == state) return;
	if (!_player) { _player = Manager::GetScene()->GetGameObject<Player>(); }
	_state = state; m_Count = 0;	_paturnNo = paturn;
}


//---------------------------------------Enemy個々の処理---------------------------------------------
void EnemyBase::LoadModel()
{
	_TransForm->_Scale = { 5.0f,2.0f,5.0f };
	//m_Model = new ModelRenderer(this);
	//m_Model->Init();
	//m_Model->Load("asset\\model\\cylinder.obj");
	//_AnimModel = new AnimationModel(this);
	//_AnimModel->Init();
	//_AnimModel->Load("asset\\model\\Akai.fbx");

}

void EnemyBase::AnimationControl()
{
	//if (_AnimModel) { _AnimModel->Update(_animationFrame); }
}
