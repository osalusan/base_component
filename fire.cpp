#include "fire.h"

void BlueFire::Update()
{
	ParticleEmiter::Update();
	//パーティクルの発射
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!_particle[i].Enable)
		{
			_particle[i].Enable = true;
			_particle[i].position = _TransForm->_Position;
			_particle[i].velocity.x = (rand() % 100 - 50) * 0.001f;
			_particle[i].velocity.z = (rand() % 100 - 50) * 0.001f;
			_particle[i].velocity.y = (rand() % 100) * 0.001f;
			_particle[i].scale = _TransForm->_Scale;
			_particle[i].color = { 0.2f,0.2f,0.8f,1.0f};
			_particle[i].lifetime = 1000.0f * (_particle[i].velocity.y) + 40.0f;
			break;
		}
	}
	//パーティクルの処理
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_particle[i].Enable)
		{
			_particle[i].position.x += _particle[i].velocity.x;
			_particle[i].position.y += _particle[i].velocity.y;
			_particle[i].position.z += _particle[i].velocity.z;

			_particle[i].lifetime--;
			if (_particle[i].lifetime <= 0)
			{
				_particle[i].Enable = false;
			}
		}

	}
}
// -------------------------------------- BlueFire_Ring --------------------------------------
void BlueFire_Ring::Update()
{
	ParticleEmiter::Update();
	//パーティクルの発射
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!_particle[i].Enable)
		{
			_particle[i].Enable = true;
			_particle[i].position = _TransForm->_Position;
			_particle[i].velocity.x = (rand() % 100 - 50) * 0.004f;
			_particle[i].velocity.z = (rand() % 100 - 50) * 0.004f;
			_particle[i].velocity.y = (rand() % 100 - 50) * 0.004f;
			float size = (rand() % 100) * 0.05f;
			_particle[i].scale.x = size;
			_particle[i].scale.z = size;
			_particle[i].scale.y = size;
			_particle[i].color = { 0.24f,0.23f,0.85f,1.0f };
			_particle[i].lifetime = 80.0f;
			break;
		}
	}
	//パーティクルの処理
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_particle[i].Enable)
		{
			_particle[i].position.x += _particle[i].velocity.x;
			_particle[i].position.y += _particle[i].velocity.y;
			_particle[i].position.z += _particle[i].velocity.z;

			_particle[i].color.x -= 0.001f;
			_particle[i].color.y -= 0.001f;
			_particle[i].color.z += 0.001f;
		
			_particle[i].lifetime--;
			if (_particle[i].lifetime <= 0)
			{
				_particle[i].Enable = false;
			}
		}

	}
}

void BlueFire_Fall::Update()
{
	ParticleEmiter::Update();
	int f = 0;
	float size = 8.0f;
	//パーティクルの発射
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!_particle[i].Enable)
		{
			float rot = (rand() % 628) * 0.01f;
			_particle[i].Enable = true;
			_particle[i].position.x = _TransForm->_Position.x;
			_particle[i].position.y = (rand() % 100) *0.3f;
			_particle[i].position.z = _TransForm->_Position.z;
			_particle[i].num = { -sinf(rot) * size ,0.0f, cosf(rot) * size };

			_particle[i].velocity.y = -(rand() % 100) * 0.003f;
			_particle[i].scale = _TransForm->_Scale;
			_particle[i].color = { (rand() % 20) * 0.01f,(rand() % 50) * 0.01f,0.8f,1.0f };
			_particle[i].lifetime = 300.0f;
		}
	}
	//パーティクルの処理
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_particle[i].Enable)
		{
			_particle[i].position.x = _TransForm->_Position.x + _particle[i].num.x;
			_particle[i].position.y += _particle[i].velocity.y;
			_particle[i].position.z = _TransForm->_Position.z + _particle[i].num.z;

			_particle[i].lifetime--;
			if (_particle[i].lifetime <= 0 || _particle[i].position.y <= 0.0f)
			{
				_particle[i].Enable = false;
			}
		}

	}
}

void BlueFire_Beam::Update()
{
	ParticleEmiter::Update();
	int f = 0;
	float size = 8.0f;
	//パーティクルの発射
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!_particle[i].Enable)
		{
			float rot = (rand() % 628) * 0.01f;
			_particle[i].Enable = true;
			_particle[i].position = _TransForm->_Position;
			_particle[i].num = { -sinf(rot) * size ,cosf(rot) * size ,sinf(rot) };

			_particle[i].position.x = _TransForm->_Position.x + _particle[i].num.x;
			_particle[i].position.y = _TransForm->_Position.y + _particle[i].num.y;
			_particle[i].position.z = _TransForm->_Position.z + _particle[i].num.z;

			float speed = 1.0f * (rand() % 100);
			_particle[i].velocity.x = _TransForm->GetForward().x * speed;
			_particle[i].velocity.z = _TransForm->GetForward().z * speed;
			_particle[i].scale = {2.0f,1.0f,2.0f};
			_particle[i].color = { (rand() % 50) * 0.01f,(rand() % 30)  * 0.01f,0.6f,1.0f };
			_particle[i].lifetime = 5.0f;
			if (f >= 200) { break; }
			f++;
		}
	}
	//パーティクルの処理
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_particle[i].Enable)
		{
			_particle[i].position.x += _particle[i].velocity.x;
			_particle[i].position.z += _particle[i].velocity.z;

			_particle[i].lifetime--;
			if (_particle[i].lifetime <= 0 || _particle[i].position.y <= 0.0f)
			{
				_particle[i].Enable = false;
			}
		}

	}
}
