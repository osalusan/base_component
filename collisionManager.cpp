#include "collisionManager.h"
#include "collision.h"
#include "manager.h"
#include "scene.h"

void CollisionManager::AddCollision(Collision collision)
{
	_collision.push_back(&collision);
}

void CollisionManager::Update()
{
	_collision.sort([](Collision* a, Collision* b) {
		 
		
		});



}
