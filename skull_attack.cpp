#include "skull_attack.h"
#include "enemy_skull.h"
#include "fire.h"
#include "manager.h"
#include "bluefireBillboard.h"
#include "collision.h"
void Skull_Sphere::SetEnemyPointer(Enemy_Skull* skull)
{
	_Skull = skull;
	_fire = Manager::GetScene()->AddGameObject_T<BlueFire_Ring>(Draw_Effect);
	if(_Model != nullptr)_Model->_visible = false;
	_collision = new Collision(this);
	_collision->Init();
}

void Skull_Sphere::Uninit()
{
	Actor::Uninit();
	_collision->Unit();
	delete _collision;
	_fire->SetDestroy();
}

void Skull_Sphere::Update()
{

	if (_Skull == nullptr)return;
	//// ‰ñ“]§Œä—p•Ï”
	//float cRot = 6.28f / 4.0f;
	//float rotation = 0.0f;

	//rotation = atan2f(_TransForm->GetTargetDirection(_Skull->_TransForm->_Position).z, _TransForm->GetTargetDirection(_Skull->_TransForm->_Position).x) * -1.0f - cRot;
	//float interpolatedRotation = Lerp_R(_TransForm->_Rotation.y, rotation, 0.1f);
	//_TransForm->_Rotation.y = interpolatedRotation;

	//XMFLOAT3 right = _TransForm->GetRight();
	//XMFLOAT3 foward = _TransForm->GetForward();

	//float speedF = 3.1f;
	//int speed = 5;
	//_TransForm->_Position = { _Skull->_TransForm->_Position.x - foward.x * speed,_Skull->_TransForm->_Position.y,_Skull->_TransForm->_Position.z - foward.z * speed };
	//_Velocity->_Velocity = { right.x * speedF , right.y * speedF , right.z * speedF };

	Actor::Update();
	_TransForm->_Position = _Skull->_TransForm->_Position;
	_fire->_TransForm->_Position = _TransForm->_Position;
	
	if (_count >= 300.0f) { SetDestroy(); }
	_count++;
}


void Skull_Sphere::CollisionControl()
{
	_collision->UpdateEnemy();
	if (_collision->_hitPlayer) {
		Manager::GetScene()->GetPlayerCharcter()->_hp -= 20.0f; SetDestroy();
	}
}
// ----------------------------- FireBullet -----------------------------
void Skull_FireBullet::SetEnemyPointer(Enemy_Skull* skull)
{
	_Skull = skull;
	_fire = Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect);
	_Model->_visible = false;
	_TransForm->_Position = { _Skull->_TransForm->_Position.x,_Skull->_TransForm->_Position.y + (_Skull->_TransForm->_Scale.y * 0.5f) ,_Skull->_TransForm->_Position.z };
	XMFLOAT3 vel = _TransForm->GetTargetDirection(Manager::GetScene()->GetPlayerCharcter()->_TransForm->_Position);
	float speed = 0.5f;
	_Velocity->_Velocity = { -vel.x * speed , 0.0f , -vel.z * speed };
	_collision = new Collision(this);
	_collision->Init();
}

void Skull_FireBullet::Update()
{

	Actor::Update();
	_fire->_TransForm->_Position = _TransForm->_Position;
	if (_count >= 200.0f) { SetDestroy(); }
	_count++;
}

void Skull_FireBullet::Uninit()
{
	Actor::Uninit();
	_collision->Unit();
	delete _collision;
	_fire->SetDestroy();
}

void Skull_FireBullet::CollisionControl()
{
	_collision->UpdateEnemyBullet();
	if (_collision->_hitPlayer) {
		Manager::GetScene()->GetPlayerCharcter()->_hp -= 7.0f; SetDestroy();
	}
}

// ----------------------------- Fall -----------------------------
void Skull_Fall::SetEnemyPointer(Enemy_Skull* skull)
{
	_Skull = skull;
	_fire = Manager::GetScene()->AddGameObject_T<BlueFire_Fall>(Draw_Effect);
	_TransForm->_Position = _Skull->_TransForm->_Position;
	_collision = new Collision(this);
	_collision->Init();
}

void Skull_Fall::Uninit()
{
	Actor::Uninit();
	_collision->Unit();
	delete _collision;
	_fire->SetDestroy();
}

void Skull_Fall::Update()
{
	Actor::Update();
	_TransForm->_Position = _Skull->_TransForm->_Position;
	_fire->_TransForm->_Position = _TransForm->_Position;
	if (_count >= 100.0f) { SetDestroy(); }
	_count++;
}

void Skull_Fall::CollisionControl()
{
	_collision->UpdateEnemy();
	if (_collision->_hitPlayer) {
		Manager::GetScene()->GetPlayerCharcter()->_hp -= 20.0f; SetDestroy();
	}
}

// ----------------------------- Beam -----------------------------
void Skull_Beam::SetEnemyPointer(Enemy_Skull* skull)
{
	_Skull = skull;
	_fire = Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect);
	_TransForm->_Position = _Skull->_TransForm->_Position;
	_collision = new Collision(this);
	_collision->Init();
	_TransForm->_Scale = { 5.0f,5.0f,5.0f };
	_Model->_visible = false;
}

void Skull_Beam::Update()
{


	if (_count >= 300) { SetDestroy();}
	if (_count <= 119) { _TransForm->_Position = _Skull->_TransForm->_Position; _TransForm->_Rotation = _Skull->_TransForm->_Rotation;}
	if (_count == 120.0f) {
		float speed = 10.0f; _Velocity->_Velocity = { _TransForm->GetForward().x * speed , 0.0f ,_TransForm->GetForward().z * speed };
		_fireBeam = Manager::GetScene()->AddGameObject_T<BlueFire_Beam>(Draw_Effect); _fireBeam->_TransForm->_Rotation = _Skull->_TransForm->_Rotation; _fireBeam->_TransForm->_Position = _Skull->_TransForm->_Position;
	}
	if (_TransForm->_Position.x >= _Skull->_TransForm->_Position.x +_TransForm->GetForward().x * 200.0f && _TransForm->_Position.z >= _Skull->_TransForm->_Position.z + _TransForm->GetForward().z * 200.0f) { 
		_TransForm->_Position = _Skull->_TransForm->_Position; };
	_count++;
	Actor::Update();
}

void Skull_Beam::Uninit()
{
	_fire->SetDestroy(); _fireBeam->SetDestroy();
}

void Skull_Beam::CollisionControl()
{
	_collision->UpdateEnemy();
	if (_collision->_hitPlayer && !_hit) {
		Manager::GetScene()->GetPlayerCharcter()->_hp -= 50.0f; _hit = true;
	}
}
