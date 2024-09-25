#include "collision.h"
#include "gameobj.h"
#include "manager.h"
#include "scene.h"
#include "gameobj.h"
#include "player.h"

void Collision::Init()
{

}

void Collision::Unit()
{

}

void Collision::Update()
{
	// Collisionを追加したGameObjectの座標を取得
	_Position = _GameObject->m_TransForm->_Position;
	_groundHit = false;
	_hit = false;
	auto otherActors = Manager::GetScene()->GetActorObjects();

	for (GameObject* otherActor : otherActors)
	{
		if (_Position.x == otherActor->m_TransForm->_Position.x &&
			_Position.y == otherActor->m_TransForm->_Position.y &&
			_Position.z == otherActor->m_TransForm->_Position.z)
		{
			// 座標が完全に一致した場合、自身の為当たり判定を取らない
		}
		else
		{

			_direction.x = otherActor->m_TransForm->_Position.x -  _Position.x;
			_direction.y = otherActor->m_TransForm->_Position.y -  _Position.y;
			_direction.z = otherActor->m_TransForm->_Position.z -  _Position.z;

			float length;
			length = sqrtf(_direction.x * _direction.x
				+ _direction.z * _direction.z);

			// 横の判定
			if (length < otherActor->m_TransForm->_Scale.x)
			{
				_otherActor = otherActor;
				//上に乗った場合
				float height = otherActor->m_TransForm->_Scale.y * 0.5f;
				if (-_direction.y > height)
				{
					_groundHeight = otherActor->m_TransForm->_Position.y + otherActor->m_TransForm->_Scale.y;
					_groundHit = true;
				}
				else if(-_direction.y < height * 2 && -_direction.y > -height)
				{
					_hit = true;
				}


			}
		}
	}

}

void Collision::Draw()
{

}

void Collision::UpdateEnemy()
{
	// Collisionを追加したGameObjectの座標を取得
	_Position = _GameObject->m_TransForm->_Position;
	_hitPlayer = false;
	auto player = Manager::GetScene()->GetPlayerCharcter();



	XMFLOAT3 direction;
	direction.x = player->m_TransForm->_Position.x - _Position.x;
	direction.y = player->m_TransForm->_Position.y - _Position.y;
	direction.z = player->m_TransForm->_Position.z - _Position.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.z * direction.z);

	float height = player->m_TransForm->_Scale.y * 0.5f;// 原点が中心の場合半分にする
	if (length < player->m_TransForm->_Scale.x * 200.0f)
	{

		if (-direction.y < height && -direction.y > -height) {
			_hitPlayer = true;
		}
		
	}
}

void Collision::UpdateEnemyBullet()
{
	// Collisionを追加したGameObjectの座標を取得
	_Position = _GameObject->m_TransForm->_Position;
	_hitPlayer = false;
	auto player = Manager::GetScene()->GetPlayerCharcter();



	XMFLOAT3 direction;
	direction.x = player->m_TransForm->_Position.x - _Position.x;
	direction.y = player->m_TransForm->_Position.y - _Position.y;
	direction.z = player->m_TransForm->_Position.z - _Position.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.z * direction.z);

	float height = player->m_TransForm->_Scale.y * 0.5f;// 原点が中心の場合半分にする
	if (length < player->m_TransForm->_Scale.x * 100.0f)
	{

		if (-direction.y > height ) {
			_hitPlayer = true;
		}

	}
}
