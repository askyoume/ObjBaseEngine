#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "IdleToMiddleKick.h"

bool Client::IdleToMiddleKick::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	if (!pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		return true;
	}

	pBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	return false;
}

void Client::IdleToMiddleKick::Remove()
{
}

Client::IdleToMiddleKick* Client::IdleToMiddleKick::Create()
{
	return new IdleToMiddleKick;
}
