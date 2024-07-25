#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/World.h"

#include "../../Engine/Headers/MovementComponent.h" //temp

#include "AI_ChasingToIdle.h"

bool Client::AI_ChasingToIdle::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	if(!pAnimationComponent->IsClipEnd("Dead"))
	{
		return false;
	}

	if (!pAnimationComponent->IsClipEnd("Hit"))
	{
		SetTargetState("AI_HIT");
		return true;
	}

	Mathf::Vector2 _distance =
	pTarget->GetRootComponent()->GetWorldLocation() -
	pActor->GetRootComponent()->GetWorldLocation();

	float distanceLocation = abs(_distance.x);

	if (500.f < distanceLocation)
	{
		SetTargetState("AI_IDLE");
		return true;
	}
	else if (100.f <= distanceLocation && 300.f >= distanceLocation)
	{
		SetTargetState("AI_CHASING");
		return true;
	}

	return false;
}

void Client::AI_ChasingToIdle::Remove()
{
}

Client::AI_ChasingToIdle* Client::AI_ChasingToIdle::Create()
{
	return new AI_ChasingToIdle;
}
