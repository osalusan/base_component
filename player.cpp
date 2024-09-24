#include "actor.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "player_camera.h"
#include "udp_client.h"
#include "swordsman_job.h"
#include "player_state.h"
#include "result.h"
#include "audio.h"
#include "gameover.h"
#include "meshfiled.h"

void Player::Init()
{
	InitComponent();
	_TransForm->_Scale = {0.03f,0.03f,0.03f};
	Manager::GetScene()->AddGameObject_T<Player_Hp>(Draw_Polygon2D);
	Manager::GetScene()->AddGameObject_T<Player_Stamina>(Draw_Polygon2D);
}

void Player::Uninit()
{
	RemoveComponent();
}

void Player::Update()
{
	//過去座標登録
	_TransForm->_RecordPosition = _TransForm->_Position;
	//移動
	Move();

	//座標の設定
	if (_hp > 0.0f)
	{
		_TransForm->_Position.x += _Velocity->_Velocity.x;
		_TransForm->_Position.y += _Velocity->_Velocity.y;
		_TransForm->_Position.z += _Velocity->_Velocity.z;
	}
	

	//攻撃
	Attack();
	//当たり判定
	CollisionControl();
	//アニメーション
	AnimationState();

	//コンポーネントの更新
	UpdateComponent();
	// 体力
	if (_hp <= 0) { _animeModel->_visible = false; Manager::SetScene<GameOver>(); }
	else { _hp += 0.02f; }
	if (_hp >= 100.0f) { _hp = 100.0f; }
}

void Player::Move()
{
	float dt = 1.0f / 60.0f;
	//サーバーにプレイヤーデータを送る
	//if (Manager::GetUDPClient()){Manager::GetUDPClient()->SendMyPlayerData({_TransForm->_Position.x,_TransForm->_Position.y,_TransForm->_Position.z },_state);}

	_Velocity->_Velocity.x = { 0.0f };
	_Velocity->_Velocity.z = { 0.0f };
	auto Camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMFLOAT3 forwardvector = Camera->_TransForm->GetForward();
	XMFLOAT3 rightvector = Camera->_TransForm->GetRight();

	// 回転制御用変数
	float cRot = 6.28f / 4.0f;
	float rotation = 0.0f;

	if (Input::GetKeyPress('A'))
	{
		_Velocity->_Velocity.x += (-rightvector.x);
		_Velocity->_Velocity.z +=  (-rightvector.z);

	}
	if (Input::GetKeyPress('D'))
	{
		_Velocity->_Velocity.x +=  rightvector.x;
		_Velocity->_Velocity.z +=  rightvector.z;
	}
	if (Input::GetKeyPress('W'))
	{
		_Velocity->_Velocity.z += forwardvector.z;
		_Velocity->_Velocity.x += forwardvector.x;

	}
	if (Input::GetKeyPress('S'))
	{
		_Velocity->_Velocity.z += (-forwardvector.z);
		_Velocity->_Velocity.x += (-forwardvector.x);
	}
	if (Input::GetKeyPress(VK_RBUTTON) || Input::GetKeyPress(VK_LSHIFT))
	{
		_dash = true;
		/*if (_animationName != "Attack" && _stamina - 0.4f >= 0.0f) { _dash = true; }*/
	}
	else if (Input::GetKeyRelease(VK_RBUTTON) || Input::GetKeyRelease(VK_LSHIFT))
	{
		_dash = false;
	}
	//ジャンプ
	if (Input::GetKeyPress(VK_SPACE))
	{
		_jump = true;
		_Velocity->_Velocity.y = 1.0f;
	}

	//斜めでも速度が変わらないように
	XMVECTOR velocityVec = XMLoadFloat3(&_Velocity->_Velocity);
	XMVECTOR normalizedVelocityVec = XMVector3Normalize(velocityVec);
	XMFLOAT3 normalizedVelocity;
	XMStoreFloat3(&normalizedVelocity, normalizedVelocityVec);

	_Velocity->_Velocity.x = normalizedVelocity.x * _moveSpeed * dt;
	_Velocity->_Velocity.z = normalizedVelocity.z * _moveSpeed * dt;

	// 重力加速度
	_Velocity->_Velocity.y += -2.5f * dt;

	// ----------------------------------アニメーションの設定----------------------------------
	// 優先順位順

	if (_dash)
	{
		SetState("Dash");

		if (_dashCount <= 10) {_Velocity->_Velocity.x *= 3.84f;_Velocity->_Velocity.z *= 3.84f; }
		else { 

			float maxspeed = 3.84f;
			float dashspeed = 1.64f;
			float speed = (maxspeed - dashspeed) / 50;
			if(_dashCount <= 60){_Velocity->_Velocity.x *= maxspeed - (_dashCount * speed); _Velocity->_Velocity.z *= maxspeed - (_dashCount * speed);}
			else { _Velocity->_Velocity.x *= dashspeed; _Velocity->_Velocity.z *= dashspeed; }
			//_stamina -= 0.4f;
		}
	}
	else SetState("Run");
	
	//if (_nextanimationName == "Idle" || _nextanimationName == "Attack") { _dash = false; }
	if (_dash) { _dashCount++; }
	else { _dashCount = 0; }


	if (_dash) { if (_Velocity->_Velocity.y <= 0.0f) { _Velocity->_Velocity.y = 0.0f; } _jump = false; }
	if (Input::GetKeyPress(VK_LCONTROL)) { _Velocity->_Velocity.y = -1.0f; }

	// スタミナ管理
	if (!_dash) { _stamina += 0.25f; }
	/*if (_dash) { _stamina -= 0.5f; }*/
	if (_stamina >= 100.0f) { _stamina = 100.0f; }
	if (_stamina <= 0.0f) { _stamina = 0.0f; _dash = false; }
	// ----------------------------------向きの設定----------------------------------
	_lerpValue = 0.1f;
	if (_nextanimationName != "Idle")
	{
		rotation = atan2f(_TransForm->GetDirection(_Velocity->_Velocity).z, _TransForm->GetDirection(_Velocity->_Velocity).x) * -1.0f + cRot;
		float interpolatedRotation = Lerp_R(_TransForm->_Rotation.y, rotation, _lerpValue);
		_TransForm->_Rotation.y = interpolatedRotation;
	}

}

void Player::CollisionControl()
{
	_Collision->Update();

	float groundHeight = 0.0f;

	if (_Collision->_hit)
	{
		_TransForm->_Position.x = _TransForm->_RecordPosition.x;
		_TransForm->_Position.z = _TransForm->_RecordPosition.z;
		//// 向こうから当たってきたら押される
		//if (_Collision->_otherActor->_TransForm->_Position.x != _Collision->_otherActor->_TransForm->_RecordPosition.x||
		//	_Collision->_otherActor->_TransForm->_Position.y != _Collision->_otherActor->_TransForm->_RecordPosition.y||
		//	_Collision->_otherActor->_TransForm->_Position.z != _Collision->_otherActor->_TransForm->_RecordPosition.z) 
		//{
		//	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };

		//	if (_Collision->_direction.x >= 0.0f) { scale.x = _Collision->_otherActor->_TransForm->_Scale.x; }
		//	else { scale.x = -_Collision->_otherActor->_TransForm->_Scale.x; }
		//	if (_Collision->_direction.z >= 0.0f) { scale.z = _Collision->_otherActor->_TransForm->_Scale.z ; }
		//	else { scale.z = -_Collision->_otherActor->_TransForm->_Scale.z; }

		//	_TransForm->_Position.x = _Collision->_otherActor->_TransForm->_Position.x + scale.x;
		//	_TransForm->_Position.z = _Collision->_otherActor->_TransForm->_Position.z + scale.z;
		//}
	}
	else if (_Collision->_groundHit)
	{
		groundHeight = _Collision->_groundHeight;
	}
	// オブジェクトに乗らなかったらフィールド優先
	float filedheight = Manager::GetScene()->GetGameObject<MeshFiled>()->GetHeight(_TransForm->_Position);
	if (groundHeight < filedheight) { groundHeight = filedheight; }


	// 地面
	if (_TransForm->_Position.y < groundHeight)
	{
		_TransForm->_Position.y = groundHeight;
		_Velocity->_Velocity.y = 0.0f;
	}


	if (_Velocity->_Velocity.y == 0) { _jump = false; }
}

void Player::AnimationState()
{
	if (_animationName != _nextanimationName && _blendRatio < 1.0f) {_blendRatio += 0.05f;}
	else if(_animationName != _nextanimationName && _blendRatio > 0.0f){ _blendRatio -= 0.05f; }

	_animeModel->Update(_animationName.c_str(), _animationFrame, _nextanimationName.c_str(), _animationFrame, _blendRatio);
	//if (_blendRatio >= 1.0f || _blendRatio <= 0.0f) { _animeModel->Update(_animationName.c_str(), _animationFrame); }
	//else { _animeModel->Update(_animationName.c_str(), _animationFrame, _nextanimationName.c_str(), _animationFrame,_blendRatio); }

	_animationFrame++;
}

void Player::SetState(std::string state)
{
	if (!_useAttack) {
		if (_nextanimationName != state){ _nextanimationName = state;}
	}

	if (_animationName != _nextanimationName && _blendRatio >= 1.0f) { _animationName = _nextanimationName; _blendRatio = 0.0f;}
}

void Player::Attack()
{
	auto Camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		//if (_stamina - 12.25f >= 0.0f)
		//{
		//	SetState("Attack");
		//	if (_punchi == nullptr) { 
		//		_punchi = Manager::GetScene()->AddGameObject_T<PlayerPunchi>(Draw_Actor); _atkCount = 0; _atkFlag = true; _useAttack = true; _stamina -= 12.25f; 
		//		_attackSE->Play(false);
		//	}
		//}
	}
	//if (!_atkFlag && !_useAttack) { _punchi = nullptr; }
	//if (_punchi != nullptr && _atkFlag) {
	//	_punchi->_TransForm->_Position = _TransForm->_Position;
	//	//_punchi->_TransForm->_Position.x = _TransForm->_Position.x + (Camera->_TransForm->GetForward().x * 5.5f);
	//	//_punchi->_TransForm->_Position.y = _TransForm->_Position.y + (3.5f);
	//	//_punchi->_TransForm->_Position.z = _TransForm->_Position.z + (Camera->_TransForm->GetForward().z * 5.5f);
	//}

	if (_nextanimationName == "Attack"&& _atkCount<= _atkTime)
	{
		_TransForm->_Rotation.y = Camera->_TransForm->_Rotation.y;
		_atkCount++;
	}
	if (_atkCount >= _atkTime) { _atkFlag = false; _useAttack = false;}
	//if (!_atkFlag && _punchi != nullptr) { _punchi->SetDestroy(); }
}

void Player::LoadModel()
{
	_animeModel->Load("asset\\model\\Akai.fbx");
	_animeModel->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	_animeModel->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
	_animeModel->LoadAnimation("asset\\model\\HurricaneKick.fbx", "Attack");
	_animeModel->LoadAnimation("asset\\model\\FallALoop.fbx", "Dash");
}

void Player::Draw()
{


	XMMATRIX world, scl, rot, trans;

	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x , _TransForm->_Position.y, _TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_animeModel) { _animeModel->Draw(); }

	DrawComponent();
}

void Player::InitComponent()
{
	_Velocity = new Velocity(this);
	_Sharder = new Sharder(this);
	_Collision = new Collision(this);
	_animeModel = new AnimationModel(this);
	_audio = new Audio(this);
	_attackSE = new Audio(this);

	_Velocity->Init();
	_Sharder->Init();
	_Collision->Init();
	_animeModel->Init();
	_audio->Load("asset\\sound\\AERIAL_FIGHT.wav");
	_attackSE->Load("asset\\sound\\seireipower.wav");
	_audio->Play(true);


	if (Manager::GetUseJob() == JOB::Job_Swordsman)
	{
		_job = new Swordsman(this);
	}
	else if (Manager::GetUseJob() == JOB::Job_wizard)
	{
		_job = new Swordsman(this);
	}
	else if (Manager::GetUseJob() == JOB::Job_Cleric)
	{
		_job = new Swordsman(this);
	}
	else if (Manager::GetUseJob() == JOB::Job_knight)
	{
		_job = new Swordsman(this);
	}
	
	if (_job) { _job->Init(); }

	LoadModel();
}

void Player::UpdateComponent()
{
	if (_Velocity) { _Velocity->Update(); };
	if (_Sharder) { _Sharder->Update(); }
	if (_job) { _job->Update(); }
}

void Player::DrawComponent()
{
	if (_Sharder) { _Sharder->Draw(); }
}

void Player::RemoveComponent()
{
	if (_audio != nullptr) { delete _audio; }
	if (_job != nullptr) { _job->Unit(); delete _job; }
	if (_animeModel != nullptr) { _animeModel->Unit(); delete _animeModel; }
	if (_Collision != nullptr) { _Collision->Unit(); delete _Collision; }
	if (_Sharder != nullptr) { _Sharder->Unit(); delete _Sharder; }
	if (_Velocity != nullptr) { _Velocity->Unit(); delete _Velocity; }

}
