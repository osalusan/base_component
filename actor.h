#pragma once
#include "gameobj.h"
//components
#include "velocity.h"
#include "sharder.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "billboard.h"
class Actor : public GameObject
{
protected:
	// コンポーネント
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};
	ModelRenderer* m_Model = {};
	AnimationModel* m_AnimeModel = {};

	// ポインタ保存用
	BillBoard* m_BillBoard = {};

	//オプション
	float m_Gravity = -2.0f;
	int m_Count = 0;
public:
	Actor() {}
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	~Actor()override;
	// ------------------ 必要に応じてオーバーライド ------------------
	virtual void Move() {}// 移動処理
	virtual void LoadModel();// モデルの読み込み処理
	virtual void CollisionControl();// 当たり判定

	// ----------------- 便利機能 ------------------
	// 回転用の線形補間
	float Lerp_R(float start, float end, float time)
	{
		// 角度の差を計算
		float difference = fmodf(end - start + DirectX::XM_PI, DirectX::XM_2PI) - DirectX::XM_PI;
		// 角度を補間
		return start + time * difference;
	}

};