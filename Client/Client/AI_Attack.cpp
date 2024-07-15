#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

#include "AI_Attack.h"

void Client::AI_Attack::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTarget = pActor->GetWorld()->FindActor("Aoko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	Mathf::Vector2 _direction = 
		pActor->GetRootComponent()->GetWorldLocation() - 
		pTarget->GetRootComponent()->GetWorldLocation();

	float nomalizeX = _direction.Normalize().x;

	if (0.f < nomalizeX)
	{
		pAnimationComponent->SetFlip(true);
	}
	else if (0.f > nomalizeX)
	{
		pAnimationComponent->SetFlip(false);
	}
}

void Client::AI_Attack::Execute(float deltaTime)
{
	if(pAnimationComponent->IsClipEnd("LowKick"))
	{
		pAnimationComponent->SetPlayClip("LowKick");
	}
}

void Client::AI_Attack::Exit()
{
	pAnimationComponent->SetFlip(false);
}

void Client::AI_Attack::Remove()
{
	//for(auto& transit : _transitions)
	//{
	//	SafeDelete(transit);
	//}
}

Client::AI_Attack* Client::AI_Attack::Create()
{
	AI_Attack* pAttack = new AI_Attack();
	pAttack->_name = "AI_ATTACK";

	return pAttack;
}
