#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/World.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "AI_IdleToAttack.h"

bool Client::AI_IdleToAttack::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
	}

	Mathf::Vector2 _distance =
	pTarget->GetRootComponent()->GetWorldLocation() -
	pActor->GetRootComponent()->GetWorldLocation();

	float distanceLocation = abs(_distance.x);
	if (100.f > distanceLocation)
	{
		SetTargetState("AI_ATTACK");
		return true;
	}
	else if (100.f <= distanceLocation && 500.f >= distanceLocation)
	{
		SetTargetState("AI_CHASING");
		return true;
	}

	return false;
}

void Client::AI_IdleToAttack::Remove()
{
}

Client::AI_IdleToAttack* Client::AI_IdleToAttack::Create()
{
    return new AI_IdleToAttack;
}
