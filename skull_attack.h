#pragma once
#include "actor.h"
#include "billboard.h"
class Enemy_Skull;
class BlueFire_Ring;
class BlueFire;
class Collision;
class BlueFire_Fall;
class BlueFire_Beam;
class Skull_Sphere : public Actor
{
private:
	Enemy_Skull* _Skull;
	BlueFire_Ring* _fire;
	XMFLOAT3 _roring;
	Collision* _collision = {};
public:
	void SetEnemyPointer(Enemy_Skull * skull);
	void Uninit()override;
	void LoadModel()override { /*_Model = new ModelRenderer(this); _Model->Init(); _Model->Load("asset\\model\\head.obj");*/ };
	void Update()override;
	void CollisionControl()override;
};

class Skull_FireBullet : public Actor
{
private:
	Enemy_Skull* _Skull;
	BlueFire* _fire;
	XMFLOAT3 _roring;
	Collision* _collision = {};
public:
	void SetEnemyPointer(Enemy_Skull* skull);
	void Update()override;
	void Uninit()override;
	void LoadModel()override { _Model = new ModelRenderer(this); _Model->Init(); _Model->Load("asset\\model\\head.obj"); };
	void CollisionControl()override;
};

class Skull_Fall : public Actor
{
private:
	Enemy_Skull* _Skull;
	BlueFire_Fall* _fire;
	XMFLOAT3 _roring;
	Collision* _collision = {};
public:
	void SetEnemyPointer(Enemy_Skull* skull);
	void Uninit()override;
	void LoadModel()override { /*_Model = new ModelRenderer(this); _Model->Init(); _Model->Load("asset\\model\\head.obj");*/ };
	void Update()override;
	void CollisionControl()override;
};
class Skull_Beam : public Actor
{
private:
	Enemy_Skull* _Skull;
	BlueFire* _fire;
	BlueFire_Beam* _fireBeam;
	XMFLOAT3 _roring;
	Collision* _collision = {};
	bool _hit = false;
public:
	void SetEnemyPointer(Enemy_Skull* skull);
	void Update()override;
	void Uninit()override;
	void LoadModel()override { _Model = new ModelRenderer(this); _Model->Init(); _Model->Load("asset\\model\\head.obj"); };
	void CollisionControl()override;
};