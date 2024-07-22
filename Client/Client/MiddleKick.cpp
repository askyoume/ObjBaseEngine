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
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
	}

	if(pAnimationComponent->IsClipEnd("JumpMiddleKick") &&
		pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		if(!pMovementComponent->IsGrounded())
		{
			if(pAnimationComponent->IsFlip())
			{
				pFootBoxComponent->SetAddOffset({ -100.f, 20.f });
			}
			else
			{
				pFootBoxComponent->SetAddOffset({ 100.f, 20.f });
			}
			pFootBoxComponent->SetSize({ 250.f, 100.f });
			pAnimationComponent->SetPlayClip("JumpMiddleKick");
		}
		else
		{
			pAnimationComponent->SetPlayClip("MiddleKick");
		}
	}

	pFootBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	pBodyBoxComponent->SetSize({ 100.f, 400.f });
}

void Client::MiddleKick::Execute(float deltaTime)
{
	if (pAnimationComponent->IsClipEnd("JumpMiddleKick") ||
		pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::MiddleKick::Exit()
{
	if(pAnimationComponent->IsClipEnd("JumpMiddleKick") ||
		pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
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
