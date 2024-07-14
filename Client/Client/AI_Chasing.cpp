#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../ObjectBaseEngine/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

#include "AI_Chasing.h"
#include "AIMovementFSMContainer.h"

void Client::AI_Chasing::Enter()
{
    if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (0.f < _direction.x)
	{
		pAnimationComponent->SetPlayClip("ReadyToMove");
	}
	else if (0.f > _direction.x)
	{
		pAnimationComponent->SetPlayClip("ReadyToBackMove");
	}
}

void Client::AI_Chasing::Execute(float deltaTime)
{
	Mathf::Vector2 _direction = 
		pTarget->GetRootComponent()->GetWorldLocation() - 
		pActor->GetRootComponent()->GetWorldLocation();

	pMovementComponent->SetInputDirection(_direction.Normalize());
	if (0.f < _direction.Normalize().x &&  
		pAnimationComponent->IsClipEnd("ReadyToMove") && 
		pAnimationComponent->IsClipEnd("Move"))
	{
		pAnimationComponent->SetPlayClip("Move");
	}
	else if (0.f > _direction.Normalize().x &&
		pAnimationComponent->IsClipEnd("ReadyToBackMove") &&
		pAnimationComponent->IsClipEnd("BackMove"))
	{
		pAnimationComponent->SetPlayClip("BackMove");
	}

	pMovementComponent->Move(deltaTime);

}

void Client::AI_Chasing::Exit()
{
	pMovementComponent->SetInputDirection(UnitVector::Zero);
}

void Client::AI_Chasing::Remove()
{
	for(auto& transit : _transitions)
	{
		SafeDelete(transit);
	}
}

Client::AI_Chasing* Client::AI_Chasing::Create()
{
	AI_Chasing* pChasing = new AI_Chasing();
	pChasing->_name = "AI_CHASING";

	return pChasing;
}
