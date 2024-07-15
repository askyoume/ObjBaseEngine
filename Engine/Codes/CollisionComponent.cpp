#include "CoreManager.h"
#include "CollisionComponent.h"
#include "IColliderReceiver.h"
#include "Actor.h"

void Core::CollisionComponent::ProcessCollision()
{
	for(auto& pOtherComponent : _currentCollisionState)
	{
		if (_previousCollisionState.find(pOtherComponent) == 
			_previousCollisionState.end())
		{
			_owner->NotifyActorBeginOverlap(pOtherComponent->GetOwner());
			pOtherComponent->GetOwner()->NotifyActorBeginOverlap(_owner);
		}	
	}

	for (auto& pOtherComponent : _previousCollisionState)
	{
		if (_currentCollisionState.find(pOtherComponent) ==
			_currentCollisionState.end())
		{
			_owner->NotifyActorEndOverlap(pOtherComponent->GetOwner());
			pOtherComponent->GetOwner()->NotifyActorEndOverlap(_owner);
		}
	}
}

void Core::CollisionComponent::ProcessCollision(Actor* pOther)
{
	_owner->NotifyActorBlock(pOther);
}

void Core::CollisionComponent::AddColliderInLayer()
{
	int index = _owner->GetLayerIndex();
	CoreManager::GetInstance()->AddCollisionQueue(index, this);

}
