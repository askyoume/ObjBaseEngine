#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "IdleToRuning.h"

bool Client::IdleToRuning::ShouldTransition()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}
	
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	//std::cout << _direction.x << std::endl;
	if (!pMovementComponent->IsGrounded())
	{
		return false;
	}

	if (pMovementComponent->IsRunning())
	{
		SetTargetState("RUNING");
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
