#pragma once
#include "job.h"

class Swordsman : public Job {
private:

public:
	using Job::Job;
	virtual void Init()override {
		m_Job = JOB::Job_Swordsman;
	};
	virtual void Unit()override {};
	virtual void Update()override {};
	virtual void Draw()override {};

	
};