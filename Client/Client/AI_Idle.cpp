#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"

#include "AI_Idle.h"
#include "AIMovementFSMContainer.h"

void Client::AI_Idle::Enter()
{
    if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	if(strcmp(_pOwnerComponent->GetCurrentStateName(),"AI_Hit"))
	pAnimationComponent->SetPlayClip("Idle");
}

void Client::AI_Idle::Execute(float deltaSeconds)
{
	pMovementComponent->SetInputDirection(UnitVector::Zero);
}

void Client::AI_Idle::Exit()
{
}

void Client::AI_Idle::Remove()
{
	for(auto& transit : _transitions)
	{
		SafeDelete(transit);
	}
}

Client::AI_Idle* Client::AI_Idle::Create()
{
	AI_Idle* pIdle = new AI_Idle();
	pIdle->_name = "AI_IDLE";

    return pIdle;
}
