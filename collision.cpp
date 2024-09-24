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
	// Collision��ǉ�����GameObject�̍��W���擾
	_Position = _GameObject->_TransForm->_Position;
	_groundHit = false;
	_hit = false;
	auto otherActors = Manager::GetScene()->GetActorObjects();

	for (GameObject* otherActor : otherActors)
	{
		if (_Position.x == otherActor->_TransForm->_Position.x &&
			_Position.y == otherActor->_TransForm->_Position.y &&
			_Position.z == otherActor->_TransForm->_Position.z)
		{
			// ���W�����S�Ɉ�v�����ꍇ�A���g�̈ד����蔻������Ȃ�
		}
		else
		{

			_direction.x = otherActor->_TransForm->_Position.x -  _Position.x;
			_direction.y = otherActor->_TransForm->_Position.y -  _Position.y;
			_direction.z = otherActor->_TransForm->_Position.z -  _Position.z;

			float length;
			length = sqrtf(_direction.x * _direction.x
				+ _direction.z * _direction.z);

			// ���̔���
			if (length < otherActor->_TransForm->_Scale.x)
			{
				_otherActor = otherActor;
				//��ɏ�����ꍇ
				float height = otherActor->_TransForm->_Scale.y * 0.5f;
				if (-_direction.y > height)
				{
					_groundHeight = otherActor->_TransForm->_Position.y + otherActor->_TransForm->_Scale.y;
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
	// Collision��ǉ�����GameObject�̍��W���擾
	_Position = _GameObject->_TransForm->_Position;
	_hitPlayer = false;
	auto player = Manager::GetScene()->GetPlayerCharcter();



	XMFLOAT3 direction;
	direction.x = player->_TransForm->_Position.x - _Position.x;
	direction.y = player->_TransForm->_Position.y - _Position.y;
	direction.z = player->_TransForm->_Position.z - _Position.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.z * direction.z);

	float height = player->_TransForm->_Scale.y * 0.5f;// ���_�����S�̏ꍇ�����ɂ���
	if (length < player->_TransForm->_Scale.x * 200.0f)
	{

		if (-direction.y < height && -direction.y > -height) {
			_hitPlayer = true;
		}
		
	}
}

void Collision::UpdateEnemyBullet()
{
	// Collision��ǉ�����GameObject�̍��W���擾
	_Position = _GameObject->_TransForm->_Position;
	_hitPlayer = false;
	auto player = Manager::GetScene()->GetPlayerCharcter();



	XMFLOAT3 direction;
	direction.x = player->_TransForm->_Position.x - _Position.x;
	direction.y = player->_TransForm->_Position.y - _Position.y;
	direction.z = player->_TransForm->_Position.z - _Position.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.z * direction.z);

	float height = player->_TransForm->_Scale.y * 0.5f;// ���_�����S�̏ꍇ�����ɂ���
	if (length < player->_TransForm->_Scale.x * 100.0f)
	{

		if (-direction.y > height ) {
			_hitPlayer = true;
		}

	}
}
