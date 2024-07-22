#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "LowKick.h"
#include "ClientFSMContainer.h"

void Client::LowKick::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	if(pAnimationComponent->IsClipEnd("JumpLowKick") &&
		pAnimationComponent->IsClipEnd("LowKick"))
	{
		if(!pMovementComponent->IsGrounded())
		{
			if (pAnimationComponent->IsFlip())
			{
				pFootBoxComponent->SetAddOffset({ -80.f, 80.f });
			}
			else
			{
				pFootBoxComponent->SetAddOffset({ 80.f, 80.f });
			}
			pFootBoxComponent->SetSize({ 200.f, 100.f });
			pAnimationComponent->SetPlayClip("JumpLowKick");
		}
		else
		{
			pAnimationComponent->SetPlayClip("LowKick");
		}
	}

	pFootBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	pBodyBoxComponent->SetSize({ 100.f, 400.f });
}

void Client::LowKick::Execute(float deltaTime)
{
	if (pAnimationComponent->IsClipEnd("JumpLowKick") ||
		pAnimationComponent->IsClipEnd("LowKick"))
	{
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::LowKick::Exit()
{
	if (pAnimationComponent->IsClipEnd("JumpLowKick") ||
		pAnimationComponent->IsClipEnd("LowKick"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	}
}

void Client::LowKick::Remove()
{
	for (auto& transit : _transitions)
	{
		SafeDelete(transit);
	}

	_transitions.clear();
}

Client::LowKick* Client::LowKick::Create()
{
	LowKick* pInstance = new LowKick;
	pInstance->_name = "LowKick";

	return pInstance;
}
