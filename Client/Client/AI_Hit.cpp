#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

#include "AI_Hit.h"

void Client::AI_Hit::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	pAnimationComponent->SetPlayClip("Hit");
}

void Client::AI_Hit::Execute(float deltaTime)
{
}

void Client::AI_Hit::Exit()
{
}

void Client::AI_Hit::Remove()
{
}

Client::AI_Hit* Client::AI_Hit::Create()
{
	AI_Hit* pInstance = new AI_Hit;
	pInstance->_name = "AI_Hit";

	return pInstance;
}
