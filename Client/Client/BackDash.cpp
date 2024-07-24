#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"

#include "BackDash.h"
#include "PlayCameraActor.h"

void Client::BackDash::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Neko");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
	}

	if(pMovementComponent->IsGrounded())
	{
		pAnimationComponent->SetPlayClip("BackDash");
	}
	else
	{
		pAnimationComponent->SetPlayClip("JumpBackDash");
	}

	if(!pAnimationComponent->IsClipEnd("JumpBackDash"))
	{
		pMovementComponent->ChangeVelocity().y = -5.f * 150.f;
	}
}

void Client::BackDash::Execute(float deltaSeconds)
{
	Mathf::Vector2 _direction =
			pTarget->GetRootComponent()->GetWorldLocation() -
			pActor->GetRootComponent()->GetWorldLocation();

	if (!pAnimationComponent->IsClipEnd("JumpBackDash") ||
		!pAnimationComponent->IsClipEnd("BackDash"))
	{
		if (0.f > _direction.x)
		{
			pMovementComponent->SetInputDirectionX(5.f);
		}
		else if (0.f < _direction.x)
		{
			pMovementComponent->SetInputDirectionX(-5.f);
		}

		pMovementComponent->Move(deltaSeconds);
	}
	else if (pAnimationComponent->IsClipEnd("JumpBackDash") &&
			 pAnimationComponent->IsClipEnd("BackDash"))
	{
		pMovementComponent->SetInputDirectionX(0.f);
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::BackDash::Exit()
{
}

void Client::BackDash::Remove()
{
}

Client::BackDash* Client::BackDash::Create()
{
	BackDash* pInstance = new BackDash;
	pInstance->_name = "BackDash";

	return pInstance;
}
