#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "IdleToMove.h"

bool Client::IdleToMove::ShouldTransition()
{
	if (!pActor)
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

	if (0.5f < _direction.x || -0.5f > _direction.x)
	{
		SetTargetState("MOVE");
		return true;
	}

    return false;
}

void Client::IdleToMove::Remove()
{
}

Client::IdleToMove* Client::IdleToMove::Create()
{
	IdleToMove* pTransit = new IdleToMove();
	return pTransit;
}
