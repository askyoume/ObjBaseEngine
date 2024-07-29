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
			_owner->NotifyActorBeginOverlap({this, pOtherComponent});
		}	
	}

	for (auto& pOtherComponent : _previousCollisionState)
	{
		if (_currentCollisionState.find(pOtherComponent) ==
			_currentCollisionState.end())
		{
			_owner->NotifyActorEndOverlap({this, pOtherComponent});
		}
	}
}

void Core::CollisionComponent::ProcessCollision(CollisionComponent* pOtherComponent)
{
	_owner->NotifyActorBlock({this, pOtherComponent});
}

void Core::CollisionComponent::AddCollisionState(CollisionComponent* pOtherComponent)
{
	_currentCollisionState.insert(pOtherComponent);
}

void Core::CollisionComponent::ClearCollisionState()
{
	_previousCollisionState.clear();
	_currentCollisionState.clear();
}

void Core::CollisionComponent::UpdateCollisionState()
{
	_previousCollisionState = _currentCollisionState;
	_currentCollisionState.clear();
}

void Core::CollisionComponent::AddColliderInLayer()
{
	#ifdef _DEBUG
		AddRenderQueueInLayer();
	#endif // _DEBUG

	int index = _owner->GetLayerIndex();
	CoreManager::GetInstance()->AddCollisionQueue(index, this);
}
