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

	pAnimationComponent->SetPlayClip("BackDash");
	pMovementComponent->ChangeVelocity().y = -400.f;
}

void Client::BackDash::Execute(float deltaTime)
{
	Mathf::Vector2 _direction =
			pTarget->GetRootComponent()->GetWorldLocation() -
			pActor->GetRootComponent()->GetWorldLocation();

	if (!pAnimationComponent->IsClipEnd("BackDash"))
	{
		if (0.f > _direction.x)
		{
			pMovementComponent->SetInputDirection({ 4.f, -0.5f });
		}
		else if (0.f < _direction.x)
		{
			pMovementComponent->SetInputDirection({ -4.f, -0.5f });
		}

		pMovementComponent->Move(deltaTime);
	}
	else if (pAnimationComponent->IsClipEnd("BackDash"))
	{
		pMovementComponent->SetInputDirection({ 0.f,0.f });
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
