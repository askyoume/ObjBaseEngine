#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/MovementComponent.h"

#include "IdleToRuning.h"

bool Client::IdleToRunning::ShouldTransition()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	if (!pMovementComponent->IsGrounded())
	{
		return false;
	}

	if (pMovementComponent->IsRunning())
	{
		SetTargetState("RUNNING");
		return true;
	}

	SetTargetState("IDLE");
	return false;
}

void Client::IdleToRunning::Remove()
{
}

Client::IdleToRunning* Client::IdleToRunning::Create()
{
	IdleToRunning* pTransit = new IdleToRunning();
	return pTransit;
}
