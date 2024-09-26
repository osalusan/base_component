#pragma once
#include "component.h"

class Collision :public Component
{

public:
	XMFLOAT3 m_Position = {};
	XMFLOAT3 m_Scale = {};
	bool _hit = false;			// メッシュに当たった
	bool _groundHit = false;	// メッシュの上部分に当たった
	float _groundHeight = 0.0f;
	GameObject* _otherActor = {};
	XMFLOAT3 _direction;
	bool _hitPlayer = false;// プレイヤーに当たった

	void Init()override;
	void Unit()override;
	void Update()override;
	void Draw()override;

	void UpdateEnemy();// エネミー側がプレイヤーと判定取るため
	void UpdateEnemyBullet();// 弾用
	using Component::Component;

};