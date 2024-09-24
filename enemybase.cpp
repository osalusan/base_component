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
	_space = Manager::GetScene()->AddGameObject_T<EnemyHpSpace_Billboard>(Draw_BillBoard);
	_helth = Manager::GetScene()->AddGameObject_T<EnemyHelth_Billboard>(Draw_BillBoard);
	_frame = Manager::GetScene()->AddGameObject_T<EnemyHpFrame_Billboard>(Draw_BillBoard);

	_space->SetEnemyPointer(this);
	_helth->SetEnemyPointer(this, _hp);
	_frame->SetEnemyPointer(this);
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
	_TransForm->_Position.x += _Velocity->_Velocity.x;
	_TransForm->_Position.y += _Velocity->_Velocity.y;
	_TransForm->_Position.z += _Velocity->_Velocity.z;

	_count++;
	if (_hp <= 0.0f) { SetDestroy(); _space->SetDestroy(); _helth->SetDestroy(); _frame->SetDestroy(); Manager::SetScene<GameClear>();}
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
	_Velocity = new Velocity(this);
	_Sharder = new Sharder(this);
	_Animation = new Animation(this);
	_Velocity->Init();
	_Sharder->Init();
	_Animation->Init();
	LoadModel();
}

void EnemyBase::UpdateComponent()
{

	if (_Velocity) { _Velocity->Update(); };
	if (_Sharder) { _Sharder->Update(); }
	if (_Model) { _Model->Update(); }
	if (_Animation) { _Animation->Update(); }

}

void EnemyBase::DrawComponent()
{
	if (_Animation) { _Animation->Draw(); }
	if (_Model) { _Model->Draw(); }
	if (_AnimModel) { _AnimModel->Draw(); }
	if (_Sharder) { _Sharder->Draw(); }
}

void EnemyBase::RemoveComponent()
{
	if (_AnimModel != nullptr)_AnimModel->Unit(); delete _AnimModel;
	if (_Animation != nullptr)_Animation->Unit(); delete _Animation;
	if (_Model != nullptr)_Model->Unit(); delete _Model;
	if (_Sharder != nullptr)_Sharder->Unit(); delete _Sharder;
	if (_Velocity != nullptr) _Velocity->Unit(); delete _Velocity;
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
	_state = state; _count = 0;

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
	_Velocity->_Velocity = { 0.0f,0.0f,0.0f };
}

void EnemyBase::SetRandState()
{
	_count = 0;
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
	_Velocity->_Velocity = { 0.0f,0.0f,0.0f };

}

void EnemyBase::SetDebugState(ENEMY_STATE state, int paturn)
{
	if (_state == state) return;
	if (!_player) { _player = Manager::GetScene()->GetGameObject<Player>(); }
	_state = state; _count = 0;	_paturnNo = paturn;
}


//---------------------------------------Enemy個々の処理---------------------------------------------
void EnemyBase::LoadModel()
{
	_TransForm->_Scale = { 5.0f,2.0f,5.0f };
	//_Model = new ModelRenderer(this);
	//_Model->Init();
	//_Model->Load("asset\\model\\cylinder.obj");
	//_AnimModel = new AnimationModel(this);
	//_AnimModel->Init();
	//_AnimModel->Load("asset\\model\\Akai.fbx");

}

void EnemyBase::AnimationControl()
{
	//if (_AnimModel) { _AnimModel->Update(_animationFrame); }
}
