#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "KickToComboStart.h"

bool Client::KickToComboStart::ShouldTransition()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	//std::cout << "KickToComboStart" << std::endl;

	if(!pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		SetTargetState("AutoComboStart");
		return true;
	}

	pBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	return false;
}

void Client::KickToComboStart::Remove()
{
}

Client::KickToComboStart* Client::KickToComboStart::Create()
{
	return new KickToComboStart;
}
