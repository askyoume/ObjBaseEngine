#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "Actor.h"

void Core::CollisionManager::SimulateCollision()
{
	for (auto& pCollision : _collisionQueue)
	{
		if (pCollision.second->GetOwner()->IsDestroyMarked())
			continue;

		if (pCollision.second->GetCollisionType() == Collision::COLLISION_IGNORE)
			continue;

		pCollision.second->UpdateCollisionState();
	}

	for(auto pCollision : _collisionQueue)
	{
		for (auto pOther : _collisionQueue)
		{
			if (pCollision == pOther)
				continue;

			if (pCollision.second->GetOwner()->IsDestroyMarked() 
				|| pOther.second->GetOwner()->IsDestroyMarked())
				continue;

			if(pCollision.second->GetCollisionType() == Collision::COLLISION_IGNORE)
				continue;

			if(!pCollision.second->GetIgnoreLayerList().empty())
			{
				for (auto& ignoreLayer : pCollision.second->GetIgnoreLayerList())
				{
					if (ignoreLayer == pOther.first)
						continue;
				}
			}

			if (pCollision.second->IsCollision(pOther.second))
			{
				if(pCollision.second->GetCollisionType() == Collision::COLLISION_BLOCK)
				{
					pCollision.second->ProcessCollision(pOther.second);
				}
				else if (pCollision.second->GetCollisionType() == Collision::COLLISION_OVERLAP)
				{
					pCollision.second->AddCollisionState(pOther.second);
					pOther.second->AddCollisionState(pCollision.second);
				}
			}
		}
	}

	for(auto& pCollision : _collisionQueue)
	{
		pCollision.second->ProcessCollision();
	}
}

void Core::CollisionManager::AddCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
	if (nullptr == pCollsionComponent)
		return;

	_collisionQueue.push_back(std::make_pair(layerIndex, pCollsionComponent));
}

void Core::CollisionManager::RemoveCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
	if (nullptr == pCollsionComponent)
		return;

	_collisionQueue.erase(
		std::find_if(_collisionQueue.begin(), _collisionQueue.end(),
			[layerIndex, pCollsionComponent](const CollsionData& data)
			{
				return data.first == layerIndex && data.second == pCollsionComponent;
			}));
}

Core::CollisionManager* Core::CollisionManager::Create()
{
	return new CollisionManager;
}

void Core::CollisionManager::Remove()
{
}
