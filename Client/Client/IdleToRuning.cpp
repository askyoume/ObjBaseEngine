#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"

#include "../../ObjectBaseEngine/MovementComponent.h" //temp

#include "Aoko.h"
#include "IdleToRuning.h"

bool Client::IdleToRuning::ShouldTransition()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}
	
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (0.5f < _direction.x || -0.5 > _direction.x)
	{
		SetTargetState("RUNING");
		//std::cout << _direction.x << std::endl;
		return true;
	}

	return false;
}

void Client::IdleToRuning::Remove()
{
}

Client::IdleToRuning* Client::IdleToRuning::Create()
{
	IdleToRuning* pTransit = new IdleToRuning();
	return pTransit;
}
