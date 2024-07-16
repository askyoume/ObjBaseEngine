#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"

#include "MiddleKick.h"
#include "ClientFSMContainer.h"

void Client::MiddleKick::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	if (pAnimationComponent->IsClipEnd("LowKick"))
	{
		pAnimationComponent->SetPlayClip("LowKick");
	}
}

void Client::MiddleKick::Execute(float deltaTime)
{
}

void Client::MiddleKick::Exit()
{
}

void Client::MiddleKick::Remove()
{
}

Client::MiddleKick* Client::MiddleKick::Create()
{
    return nullptr;
}
