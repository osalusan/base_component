#pragma once
#include "component.h"

enum class JOB {
	Job_None = 0,
	Job_Swordsman,
	Job_wizard,
	Job_Cleric,
	Job_knight,
	Job_Max
};
enum class ATTACK {
	Attack_None = 0,
	Attack_Normal,
	Attack_Skill ,
	Attack_Special,
	Attack_Max
};
class Job :public Component
{
protected:
	
public: 
	//PLAYER_STATE _state = PLAYER_STATE::PLAYER_MAX;
	JOB _job = JOB::Job_None;
	ATTACK _attack = ATTACK::Attack_None;
	//enum class PLAYER_STATE _playerState = PLAYER_STATE::PLAYER_MAX;
	using Component::Component;
	virtual void Init()override {};
	virtual void Unit()override {};
	virtual void Update()override {};
	virtual void Draw()override {};
	

};