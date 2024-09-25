#include "actor.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "player_camera.h"
#include "udp_client.h"
#include "player_state.h"
#include "result.h"
#include "audio.h"
#include "gameover.h"
#include "meshfiled.h"

void Player::Init()
{
	InitComponents();
	m_TransForm->_Scale = {0.03f,0.03f,0.03f};
	Manager::GetScene()->AddGameObject_T<Player_Hp>(Draw_Polygon2D);
	Manager::GetScene()->AddGameObject_T<Player_Stamina>(Draw_Polygon2D);
}

void Player::Uninit()
{
	RemoveComponents();
}

void Player::Update()
{
	//過去座標登録
	m_TransForm->_RecordPosition = m_TransForm->_Position;
	//移動
	Move();

	//座標の設定
	if (m_Hp > 0.0f)
	{
		m_TransForm->_Position.x += m_Velocity->m_Velocity.x;
		m_TransForm->_Position.y += m_Velocity->m_Velocity.y;
		m_TransForm->_Position.z += m_Velocity->m_Velocity.z;
	}
	

	//攻撃
	Attack();
	//当たり判定
	CollisionControl();
	//アニメーション
	AnimationState();
	//コンポーネントの更新
	UpdateComponents();
	// 体力
	if (m_Hp <= 0) { mm_AnimeModel->_visible = false; Manager::SetScene<GameOver>(); }
	else { m_Hp += 0.02f; }
	if (m_Hp >= 100.0f) { m_Hp = 100.0f; }
}

void Player::Move()
{
	float dt = 1.0f / 60.0f;
	//サーバーにプレイヤーデータを送る
	//if (Manager::GetUDPClient()){Manager::GetUDPClient()->SendMyPlayerData({m_TransForm->_Position.x,m_TransForm->_Position.y,m_TransForm->_Position.z },_state);}

	m_Velocity->m_Velocity.x = { 0.0f };
	m_Velocity->m_Velocity.z = { 0.0f };
	auto Camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMFLOAT3 forwardvector = Camera->m_TransForm->GetForward();
	XMFLOAT3 rightvector = Camera->m_TransForm->GetRight();

	// 回転制御用変数
	float cRot = 6.28f / 4.0f;
	float rotation = 0.0f;

	if (Input::GetKeyPress('A'))
	{
		m_Velocity->m_Velocity.x += (-rightvector.x);
		m_Velocity->m_Velocity.z +=  (-rightvector.z);

	}
	if (Input::GetKeyPress('D'))
	{
		m_Velocity->m_Velocity.x +=  rightvector.x;
		m_Velocity->m_Velocity.z +=  rightvector.z;
	}
	if (Input::GetKeyPress('W'))
	{
		m_Velocity->m_Velocity.z += forwardvector.z;
		m_Velocity->m_Velocity.x += forwardvector.x;

	}
	if (Input::GetKeyPress('S'))
	{
		m_Velocity->m_Velocity.z += (-forwardvector.z);
		m_Velocity->m_Velocity.x += (-forwardvector.x);
	}
	if (Input::GetKeyPress(VK_RBUTTON) || Input::GetKeyPress(VK_LSHIFT))
	{
		m_Dash = true;
		/*if (_animationName != "Attack" && _stamina - 0.4f >= 0.0f) { _dash = true; }*/
	}
	else if (Input::GetKeyRelease(VK_RBUTTON) || Input::GetKeyRelease(VK_LSHIFT))
	{
		m_Dash = false;
	}
	//ジャンプ
	if (Input::GetKeyPress(VK_SPACE))
	{
		m_Jump = true;
		m_Velocity->m_Velocity.y = 1.0f;
	}

	//斜めでも速度が変わらないように
	XMVECTOR velocityVec = XMLoadFloat3(&m_Velocity->m_Velocity);
	XMVECTOR normalizedVelocityVec = XMVector3Normalize(velocityVec);
	XMFLOAT3 normalizedVelocity;
	XMStoreFloat3(&normalizedVelocity, normalizedVelocityVec);

	m_Velocity->m_Velocity.x = normalizedVelocity.x * m_MoveSpeed * dt;
	m_Velocity->m_Velocity.z = normalizedVelocity.z * m_MoveSpeed * dt;

	// 重力加速度
	m_Velocity->m_Velocity.y += -2.5f * dt;

	// ----------------------------------アニメーションの設定----------------------------------
	// 優先順位順

	if (m_Dash)
	{
		SetState("Dash");

		if (m_DashCount <= 10) {m_Velocity->m_Velocity.x *= 3.84f;m_Velocity->m_Velocity.z *= 3.84f; }
		else { 

			float maxspeed = 3.84f;
			float dashspeed = 1.64f;
			float speed = (maxspeed - dashspeed) / 50;
			if(m_DashCount <= 60){m_Velocity->m_Velocity.x *= maxspeed - (m_DashCount * speed); m_Velocity->m_Velocity.z *= maxspeed - (m_DashCount * speed);}
			else { m_Velocity->m_Velocity.x *= dashspeed; m_Velocity->m_Velocity.z *= dashspeed; }
			//_stamina -= 0.4f;
		}
	}
	else 
	{
		if (m_Velocity->m_Velocity.x != 0) { SetState("Run"); }
		else { SetState("Idle"); }
	}
	//if (_nextanimationName == "Idle" || _nextanimationName == "Attack") { _dash = false; }
	if (m_Dash) { m_DashCount++; }
	else { m_DashCount = 0; }


	if (m_Dash) { if (m_Velocity->m_Velocity.y <= 0.0f) { m_Velocity->m_Velocity.y = 0.0f; } m_Jump = false; }
	if (Input::GetKeyPress(VK_LCONTROL)) { m_Velocity->m_Velocity.y = -1.0f; }

	// スタミナ管理
	if (!m_Dash) { m_Stamina += 0.25f; }
	/*if (_dash) { _stamina -= 0.5f; }*/
	if (m_Stamina >= 100.0f) { m_Stamina = 100.0f; }
	if (m_Stamina <= 0.0f) { m_Stamina = 0.0f; m_Dash = false; }
	// ----------------------------------向きの設定----------------------------------
	_lerpValue = 0.1f;
	if (m_NextanimationName != "Idle")
	{
		rotation = atan2f(m_TransForm->GetDirection(m_Velocity->m_Velocity).z, m_TransForm->GetDirection(m_Velocity->m_Velocity).x) * -1.0f + cRot;
		float interpolatedRotation = Lerp_R(m_TransForm->_Rotation.y, rotation, _lerpValue);
		m_TransForm->_Rotation.y = interpolatedRotation;
	}

}

void Player::CollisionControl()
{
	m_Collision->Update();

	float groundHeight = 0.0f;

	if (m_Collision->_hit)
	{
		m_TransForm->_Position.x = m_TransForm->_RecordPosition.x;
		m_TransForm->_Position.z = m_TransForm->_RecordPosition.z;
		//// 向こうから当たってきたら押される
		//if (m_Collision->_otherActor->m_TransForm->_Position.x != m_Collision->_otherActor->m_TransForm->_RecordPosition.x||
		//	m_Collision->_otherActor->m_TransForm->_Position.y != m_Collision->_otherActor->m_TransForm->_RecordPosition.y||
		//	m_Collision->_otherActor->m_TransForm->_Position.z != m_Collision->_otherActor->m_TransForm->_RecordPosition.z) 
		//{
		//	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };

		//	if (m_Collision->_direction.x >= 0.0f) { scale.x = m_Collision->_otherActor->m_TransForm->_Scale.x; }
		//	else { scale.x = -m_Collision->_otherActor->m_TransForm->_Scale.x; }
		//	if (m_Collision->_direction.z >= 0.0f) { scale.z = m_Collision->_otherActor->m_TransForm->_Scale.z ; }
		//	else { scale.z = -m_Collision->_otherActor->m_TransForm->_Scale.z; }

		//	m_TransForm->_Position.x = m_Collision->_otherActor->m_TransForm->_Position.x + scale.x;
		//	m_TransForm->_Position.z = m_Collision->_otherActor->m_TransForm->_Position.z + scale.z;
		//}
	}
	else if (m_Collision->_groundHit)
	{
		groundHeight = m_Collision->_groundHeight;
	}
	// オブジェクトに乗らなかったらフィールド優先
	float filedheight = Manager::GetScene()->GetGameObject<MeshFiled>()->GetHeight(m_TransForm->_Position);
	if (groundHeight < filedheight) { groundHeight = filedheight; }


	// 地面
	if (m_TransForm->_Position.y < groundHeight)
	{
		m_TransForm->_Position.y = groundHeight;
		m_Velocity->m_Velocity.y = 0.0f;
	}


	if (m_Velocity->m_Velocity.y == 0) { m_Jump = false; }
}

void Player::AnimationState()
{
	if (m_AnimationName != m_NextanimationName && m_BlendRatio < 1.0f) {m_BlendRatio += 0.05f;}
	else if(m_AnimationName != m_NextanimationName && m_BlendRatio > 0.0f){ m_BlendRatio -= 0.05f; }

	mm_AnimeModel->Update(m_AnimationName.c_str(), m_AnimationFrame, m_NextanimationName.c_str(), m_AnimationFrame, m_BlendRatio);
	//if (_blendRatio >= 1.0f || _blendRatio <= 0.0f) { mm_AnimeModel->Update(_animationName.c_str(), _animationFrame); }
	//else { mm_AnimeModel->Update(_animationName.c_str(), _animationFrame, _nextanimationName.c_str(), _animationFrame,_blendRatio); }

	m_AnimationFrame++;
}

void Player::SetState(std::string state)
{
	if (!m_UseAttack) {
		if (m_NextanimationName != state){ m_NextanimationName = state;}
	}

	if (m_AnimationName != m_NextanimationName && m_BlendRatio >= 1.0f) { m_AnimationName = m_NextanimationName; m_BlendRatio = 0.0f; m_AnimationFrame = 0; }
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
		//		m_AttackSE->Play(false);
		//	}
		//}
	}
	//if (!_atkFlag && !_useAttack) { _punchi = nullptr; }
	//if (_punchi != nullptr && _atkFlag) {
	//	_punchi->m_TransForm->_Position = m_TransForm->_Position;
	//	//_punchi->m_TransForm->_Position.x = m_TransForm->_Position.x + (Camera->m_TransForm->GetForward().x * 5.5f);
	//	//_punchi->m_TransForm->_Position.y = m_TransForm->_Position.y + (3.5f);
	//	//_punchi->m_TransForm->_Position.z = m_TransForm->_Position.z + (Camera->m_TransForm->GetForward().z * 5.5f);
	//}

	if (m_NextanimationName == "Attack"&& m_AtkCount<= m_AtkTime)
	{
		m_TransForm->_Rotation.y = Camera->m_TransForm->_Rotation.y;
		m_AtkCount++;
	}
	if (m_AtkCount >= m_AtkTime) { m_AtkFlag = false; m_UseAttack = false;}
	//if (!_atkFlag && _punchi != nullptr) { _punchi->SetDestroy(); }
}

void Player::LoadModel()
{
	mm_AnimeModel->Load("asset\\model\\Akai.fbx");
	mm_AnimeModel->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	mm_AnimeModel->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
	mm_AnimeModel->LoadAnimation("asset\\model\\HurricaneKick.fbx", "Attack");
	mm_AnimeModel->LoadAnimation("asset\\model\\FallALoop.fbx", "Dash");
}

void Player::Draw()
{
	DrawComponents();

	XMMATRIX world, scl, rot, trans;

	scl = XMMatrixScaling(m_TransForm->_Scale.x, m_TransForm->_Scale.y, m_TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->_Rotation.x, m_TransForm->_Rotation.y, m_TransForm->_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->_Position.x , m_TransForm->_Position.y, m_TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (mm_AnimeModel) { mm_AnimeModel->Draw(); }
}

void Player::InitComponents()
{
	m_Velocity = new Velocity(this);
	m_Sharder = new Sharder(this);
	m_Collision = new Collision(this);
	mm_AnimeModel = new AnimationModel(this);
	m_AttackSE = new Audio(this);

	m_Velocity->Init();
	m_Sharder->m_Usesharder = 2; m_Sharder->Init();
	m_Collision->Init();
	mm_AnimeModel->Init();
	m_AttackSE->Load("asset\\sound\\seireipower.wav");

	LoadModel();
}

void Player::UpdateComponents()
{
	 m_Velocity->Update(); 
	m_Sharder->Update(); 
}

void Player::DrawComponents()
{
	 m_Sharder->Draw(); 
}

void Player::RemoveComponents()
{
	if (mm_AnimeModel != nullptr) { mm_AnimeModel->Unit(); delete mm_AnimeModel; }
	if (m_Collision != nullptr) { m_Collision->Unit(); delete m_Collision; }
	if (m_Sharder != nullptr) { m_Sharder->Unit(); delete m_Sharder; }
	if (m_Velocity != nullptr) { m_Velocity->Unit(); delete m_Velocity; }

}
