#pragma once
#include "actor.h"
#include "collision.h"
class PlayerPunchi : public Actor
{
private:
	Collision* _Collision = {};

public:
	void LoadModel()override;
	void CollisionControl()override;

};