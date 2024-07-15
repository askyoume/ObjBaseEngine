#include "CollisionManager.h"
#include "CollisionComponent.h"

void Core::CollisionManager::SimulateCollision()
{
	for(auto& pCollision : _collisionQueue)
	{
		for (auto& pOther : _collisionQueue)
		{
			if (pCollision == pOther)
				continue;

			//if()
		}
	}
}

void Core::CollisionManager::AddCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
}

void Core::CollisionManager::RemoveCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
}

Core::CollisionManager* Core::CollisionManager::Create()
{
	return nullptr;
}

void Core::CollisionManager::Remove()
{
}
