#pragma once
#include "gameobj.h"
#include "velocity.h"
#include "modelRenderer.h"
#include "sharder.h"
#include "animation.h"
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
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};
	Collision* m_Collision = {};
	AnimationModel* m_AnimeModel = {};
	ModelRenderer* m_ChildModel = {};
	Audio* m_AttackSE = {};


	float m_MoveSpeed = 15.00f;
	bool m_Dash = false;			  // ダッシュ中
	bool m_Jump = false;			  // ジャンプ中
	bool m_ChengeAnimation = false;// アニメーションが今変えられるかどうか
	unsigned int m_AnimationFrame = 0;	  // アニメーションのフレーム
	std::string m_AnimationName = "Idle";// アニメーションの名前
	std::string m_NextanimationName = "Idle";// ブレンド用、次のアニメーションの名前
	float m_BlendRatio = 1.0f;// アニメーションブレンドの数値
	bool m_UseAttack = false;

	float _lerpValue = 0;


	int m_AtkCount = 0;
	int m_AtkTime = 100.0f;
	int m_DashCount = 0;
	
public:
	bool m_AtkFlag = false;// 攻撃が当たった
	float m_Hp = 100.0f;// 体力
	float m_Stamina = 100.0f;// スタミナ

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
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