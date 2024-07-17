#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"

#include "MiddleKick.h"
#include "ClientFSMContainer.h"

void Client::MiddleKick::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
	}

	if(pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		pBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
		pAnimationComponent->SetPlayClip("MiddleKick");
	}
}

void Client::MiddleKick::Execute(float deltaTime)
{
	if (pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::MiddleKick::Exit()
{
	if(pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		pBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	}
}

void Client::MiddleKick::Remove()
{
	for (auto& transit : _transitions)
	{
		SafeDelete(transit);
	}

	_transitions.clear();
}

Client::MiddleKick* Client::MiddleKick::Create()
{
	MiddleKick* pInstance = new MiddleKick;
	pInstance->_name = "MiddleKick";

	return pInstance;
}
