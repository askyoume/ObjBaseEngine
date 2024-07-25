#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/Actor.h"


#include "AI_Dead.h"
#include "AIMovementFSMContainer.h"

void Client::AI_Dead::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BoxComponent");
	}

	if(pAnimationComponent->IsClipEnd("Dead"))
	{
		pAnimationComponent->SetPlayClip("Dead");
	}
}

void Client::AI_Dead::Execute(float deltaSeconds)
{
}

void Client::AI_Dead::Exit()
{
	pBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
}

void Client::AI_Dead::Remove()
{
	for(auto& transit : _transitions)
	{
		SafeDelete(transit);
	}
}

Client::AI_Dead* Client::AI_Dead::Create()
{
	AI_Dead* pDead = new AI_Dead();
	pDead->_name = "AI_DEAD";
	pDead->_isEndState = true;

	return pDead;
}
