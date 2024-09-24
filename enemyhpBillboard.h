#pragma once
#include "billboard.h"
class EnemyBase;
class EnemyHelth_Billboard :public BillBoard
{
private:
	EnemyBase* _enemy = {};
	float _maxhp = 0.0f;
public:
	void LoadTexture()override;
	void SetEnemyPointer(EnemyBase * enemy,float hp);
	void Update()override;
	void Draw()override;
};

class EnemyHpFrame_Billboard :public BillBoard
{
private:
	EnemyBase* _enemy = {};
public:
	void LoadTexture()override;
	void SetEnemyPointer(EnemyBase* enemy);
	void Update()override;
};

class EnemyHpSpace_Billboard :public BillBoard
{
private:
	EnemyBase* _enemy = {};
public:
	void LoadTexture()override;
	void SetEnemyPointer(EnemyBase* enemy);
	void Update()override;
};