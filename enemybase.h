#pragma once
#include "gameobj.h"
#include <cstdlib> 
#include "player.h"
#include "enemyhpBillboard.h"
//components
#include "velocity.h"
#include "sharder.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "animation.h"

enum class ENEMY_STATE {
	Enemy_Idel = 0,
	Enemy_Search,
	Enemy_Move,
	Enemy_Attack,
	Enemy_Stagger,
	Enemy_Down

};

//typedef enum {
//	ENEMY_ATTACKNO_1 =0, 
//	ENEMY_ATTACKNO_2,
//	ENEMY_ATTACKNO_3,
//	ENEMY_ATTACKNO_4,
//	ENEMY_ATTACKNO_5,
//	ENEMY_ATTACKNO_6,
//}ENEMY_ATTACK;


class EnemyBase : public GameObject {
protected:
	Velocity* _Velocity = {};
	Sharder* _Sharder = {};
	ModelRenderer* _Model = {};
	AnimationModel* _AnimModel = {};
	Animation* _Animation = {};
	Player* _player = {};
	ENEMY_STATE _state = ENEMY_STATE::Enemy_Search;
	int _attack = 0;
	int _animationFrame = 0;
	float _lerpValue = 0;
	int _count = 0;

	int _idleNo = 0;
	int _atkNo = 0;
	int _moveNo = 0;
	int _downNo = 0;

	int _idleMax = 0;
	int _atkMax = 0;
	int _moveMax = 0;
	int _downMax = 0;

	int _paturnNo = 0;// 乱数の結果

	float _stanValue = 0;


	EnemyHelth_Billboard* _helth = {};
	EnemyHpFrame_Billboard* _frame = {};
	EnemyHpSpace_Billboard* _space = {};
public:
	float _hp = 0;
	EnemyBase();
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	virtual~EnemyBase()override;
	virtual void EnemyAnimation();
	virtual void EnemyStateControl();// EnemyのState内を管理
	virtual void SetState(ENEMY_STATE state); // Stateの設定
	virtual void SetRandState();// Stateのランダム設定用
	virtual void SetDebugState(ENEMY_STATE state, int paturn);

	// ----------------State内の専用の処理------------------
	virtual void StateIdel() {};
	virtual void StateSearch() {};
	virtual void StateMove() {};
	virtual void StateAttack() {};
	virtual void StateStagger() {};
	virtual void StateDown() {};

	// ----------------Enemy個々の処理------------------
	//virtual void Move() {}// 移動処理
	//virtual void Attack() {}// 攻撃処理
	virtual void LoadModel();// モデルの読み込み処理
	virtual void AnimationControl();// AnimationModelのアニメーション
	virtual void StateControl() {};// stateの管理
	virtual void SetMaxPaturn() {};// paturnの最大数

	//プレイヤーに向かって回転
	virtual void RotationPlayer() {
		if (_player == nullptr)return;
		_lerpValue = 0.1f;
		// 回転制御用変数
		float cRot = 6.28f / 4.0f;
		float rotation = 0.0f;

		rotation = atan2f(_TransForm->GetTargetDirection(_player->_TransForm->_Position).z, _TransForm->GetTargetDirection(_player->_TransForm->_Position).x) * -1.0f - cRot ;
		float interpolatedRotation = Lerp_R(_TransForm->_Rotation.y, rotation, _lerpValue);
		_TransForm->_Rotation.y = interpolatedRotation;
	}

	virtual void RotationTargetPlayer() 
	{
		float cRot = 6.28f / 4.0f;
		float rotation = 0.0f;

		rotation = atan2f(_TransForm->GetTargetDirection(_player->_TransForm->_Position).z, _TransForm->GetTargetDirection(_player->_TransForm->_Position).x) * -1.0f - cRot;
		_TransForm->_Rotation.y = rotation;
	}

	// 回転用の線形補間
	float Lerp_R(float start, float end, float time)
	{
		// 角度の差を計算
		float difference = fmodf(end - start + XM_PI, XM_2PI) - XM_PI;
		// 角度を補間
		return start + time * difference;
	}
};