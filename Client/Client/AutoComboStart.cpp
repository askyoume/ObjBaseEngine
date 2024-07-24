#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "AutoComboStart.h"

void Client::AutoComboStart::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTargetActor = ::Core::CoreManager::GetInstance()->GetWorld()->FindActor("Neko");
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
	}


	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_BLOCK);
		pAnimationComponent->SetPlayClip("AutoComboStart");
	}
}

void Client::AutoComboStart::Execute(float deltaSeconds)
{
	float locationX = pActor->GetRootComponent()->GetRelativeLocation().x;
	float targetX	= pTargetActor->GetRootComponent()->GetRelativeLocation().x;
	float direction = locationX - targetX;
	float distanceX = abs(targetX - locationX);

	if(50.f < distanceX)
	{
		if(0.f > direction)
		{
			pMovementComponent->SetInputDirection({ 1.f,0.f });
		}
		else if (0.f < direction)
		{
			pMovementComponent->SetInputDirection({ -1.f,0.f });
		}

		pMovementComponent->Move(deltaSeconds);
	}

	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		_pOwnerComponent->ForceCheckTransition("AirLaunch");
	}
}

void Client::AutoComboStart::Exit()
{
	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		pMovementComponent->SetInputDirection({ 0.f,0.f });
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	}
}

void Client::AutoComboStart::Remove()
{
	for (auto& transit : _transitions)
	{
		SafeDelete(transit);
	}

	_transitions.clear();
}

Client::AutoComboStart* Client::AutoComboStart::Create()
{
	AutoComboStart* pInstance = new AutoComboStart;
	pInstance->_name = "AutoComboStart";

	return pInstance;
}
