#pragma once
#include "particleEmiter.h"

class BlueFire :public ParticleEmiter
{
private:

public:
	void Update()override;
};

class BlueFire_Ring :public ParticleEmiter
{
private:
	int _ring = 0;
public:
	void Update()override;
};
class BlueFire_Fall :public ParticleEmiter
{
private:

public:
	void Update()override;
};
class BlueFire_Beam :public ParticleEmiter
{
private:

public:
	void Update()override;
};