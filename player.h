#pragma once
#include "gameobj.h"
#include "velocity.h"
#include "modelRenderer.h"
#include "sharder.h"
#include "animation.h"
#include "job.h"
#include "collision.h"
#include "animationModel.h"
#include "audio.h"

#define DISTANCE_HAND (1.7f)	//手と体の距離
#define DISTANCE_LEG (0.7f)
#define MAX_PARTS (6)				//パーツの分割数

enum class PLAYER_STATE {
	PLAYER_IDEL =0,
	PLAYER_WALK,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_ATTACK,
	PLAYER_AVOIDANCE,
	PLAYER_GARD,
	PLAYER_DOWN,
	PLAYER_MAX

};

//ゲストから受け取る用の構造体
typedef struct OtherPlayerData {
	int playerID = 0;
	PLAYER_STATE playerState;
	XMFLOAT3 pos = {};
};
class Player :public GameObject {
private:
	Velocity* _Velocity = {};
	Sharder* _Sharder = {};
	Collision* _Collision = {};
	AnimationModel* _animeModel = {};
	Audio* _attackSE = {};

	Job* _job = {};

	float _moveSpeed = 15.00f;
	bool _dash = false;			  // ダッシュ中
	bool _jump = false;			  // ジャンプ中
	bool _chengeAnimation = false;// アニメーションが今変えられるかどうか
	int _animationFrame = 0;	  // アニメーションのフレーム
	std::string _animationName = "Idle";// アニメーションの名前
	std::string _nextanimationName = "Idle";// ブレンド用、次のアニメーションの名前
	float _blendRatio = 1.0f;// アニメーションブレンドの数値
	bool _useAttack = false;

	float _lerpValue = 0;


	int _atkCount = 0;
	int _atkTime = 100.0f;
	int _dashCount = 0;
	
public:
	bool _atkFlag = false;// 攻撃が当たった
	float _hp = 100.0f;// 体力
	float _stamina = 100.0f;// スタミナ

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	void Move();
	void CollisionControl();
	void AnimationState();
	void SetState(std::string state);
	void Attack();
	void LoadModel();

	// ----------------- 便利機能 ------------------
	// 回転用の線形補間
	float Lerp_R(float start, float end, float time)
	{
		// 角度の差を計算
		float difference = fmodf(end - start + XM_PI, XM_2PI) - XM_PI;
		// 角度を補間
		return start + time * difference;
	}
};