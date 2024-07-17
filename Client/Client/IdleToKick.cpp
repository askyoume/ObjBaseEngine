#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "IdleToKick.h"

bool Client::IdleToKick::ShouldTransition()
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

void Client::IdleToKick::Remove()
{
}

Client::IdleToKick* Client::IdleToKick::Create()
{
    return new IdleToKick;
}
