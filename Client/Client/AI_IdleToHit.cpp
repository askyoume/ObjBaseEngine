#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/World.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "AI_IdleToHit.h"

bool Client::AI_IdleToHit::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	if(!pAnimationComponent->IsClipEnd("Hit"))
	{
		SetTargetState("AI_HIT");
		return true;
	}

    return false;
}

void Client::AI_IdleToHit::Remove()
{
}

Client::AI_IdleToHit* Client::AI_IdleToHit::Create()
{
    return new AI_IdleToHit;
}
