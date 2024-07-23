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
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	//std::cout << "IdleToMove" << std::endl;
	if (!pMovementComponent->IsGrounded() && !pAnimationComponent->IsClipEnd("JumpBackDash"))
	{
		SetTargetState("BackDash");
		return true;
	}
	else if (!pMovementComponent->IsGrounded())
	{
		return false;
	}

	if (!pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		return false;
	}

	if (!pAnimationComponent->IsClipEnd("LowKick"))
	{
		return false;
	}

	if (!pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		SetTargetState("AutoComboStart");
		return true;
	}

	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
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
