#pragma once
#include "component.h"

class Collision :public Component
{

public:
	XMFLOAT3 m_Position = {};
	XMFLOAT3 m_Scale = {};
	bool _hit = false;			// ���b�V���ɓ�������
	bool _groundHit = false;	// ���b�V���̏㕔���ɓ�������
	float _groundHeight = 0.0f;
	GameObject* _otherActor = {};
	XMFLOAT3 _direction;
	bool _hitPlayer = false;// �v���C���[�ɓ�������

	void Init()override;
	void Unit()override;
	void Update()override;
	void Draw()override;

	void UpdateEnemy();// �G�l�~�[�����v���C���[�Ɣ����邽��
	void UpdateEnemyBullet();// �e�p
	using Component::Component;

};