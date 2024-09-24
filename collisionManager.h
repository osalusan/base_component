#pragma once
#include <list>

class Collision;
class CollisionManager
{
private:
	std::list<Collision*> _collision;
public:

	void AddCollision(Collision collision);
	void Update();

};