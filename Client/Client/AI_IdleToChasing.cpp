#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/World.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "AI_IdleToChasing.h"

bool Client::AI_IdleToChasing::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	if (!pAnimationComponent->IsClipEnd("Hit"))
	{
		SetTargetState("AI_Hit");
		return true;
	}

	Mathf::Vector2 _distance =
	pTarget->GetRootComponent()->GetWorldLocation() -
	pActor->GetRootComponent()->GetWorldLocation();

	float distanceLocation = abs(_distance.x);

	if (100.f <= distanceLocation && 300.f >= distanceLocation)
	{
		SetTargetState("AI_CHASING");
		return true;
	}
	else if (100.f > distanceLocation)
	{
		SetTargetState("AI_ATTACK");
		return true;
	}

	return false;
}

void Client::AI_IdleToChasing::Remove()
{
}

Client::AI_IdleToChasing* Client::AI_IdleToChasing::Create()
{
    return new AI_IdleToChasing;
}
