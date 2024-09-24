#pragma once
#include "enemybase.h"
#include "player.h"
class Enemy_Skull : public EnemyBase {
private:
	int _move = 0;//どの動きをするか
	float _rotate = 0.0f;// プレイヤーの周りを回るときに使用
public:
	void LoadModel()override;
	//void Move()override;
	void SetMaxPaturn()override;
	void StateControl()override;
	void StateIdel()override;
	void StateSearch()override;
	void StateMove()override;
	void StateAttack()override;
	void StateStagger()override;
	void StateDown()override;

};
enum IDLE_SKULL {
	Idle_Floating = 0,
	Idle_Max
};
enum ATK_SKULL {
	Atk_Takkel = 0,
	Atk_RoringFireBullet,
	Atk_Fall,
	Atk_Beam,
	Atk_Max
};
enum MOVE_SKULL {
	Move_Back = 0,
	Move_Right,
	Move_Stop,
	Move_Max
};
enum DOWN_SKULL {
	Down_Nock = 0,
	Down_Max
};