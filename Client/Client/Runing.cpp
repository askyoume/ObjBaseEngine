#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"

#include "Runing.h"
#include "ClientFSMContainer.h"

void Client::Running::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		//if (*pActor == "Player1")
		//	pTargetActor = ::Core::CoreManager::GetInstance()->GetWorld()->FindActor("Player2");
		//else
		//	pTargetActor = ::Core::CoreManager::GetInstance()->GetWorld()->FindActor("Player1");
		//°ñ¾ÆÇÁ³×? ¤»¤»¤» test code
		pTargetActor = ::Core::CoreManager::GetInstance()->GetWorld()->FindActor("Neko");
		//test code end
		pMovementComponent	= pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
	}

	pAnimationComponent->SetPlayClip("ReadyToRunning");
	pBoxComponent->SetSize({ 450.f, 600.f });
}

void Client::Running::Execute(float deltaSeconds)
{
	float locationX = pActor->GetRootComponent()->GetRelativeLocation().x;
	float targetX	= pTargetActor->GetRootComponent()->GetRelativeLocation().x;
	float direction = locationX - targetX;
	float distanceX = abs(targetX - locationX);

	if( pMovementComponent->IsRunning() && 
		!pMovementComponent->IsJumping() &&
		pAnimationComponent->IsClipEnd("ReadyToRunning") &&
		pAnimationComponent->IsClipEnd("Running"))
	{
		pAnimationComponent->SetPlayClip("Running");
	}

	if(250.f < distanceX)
	{
		pMovementComponent->SetRunning(true);
		if(0.f > direction)
		{
			pMovementComponent->SetInputDirection({ 3.f,0.f });
		}
		else if (0.f < direction)
		{
			pMovementComponent->SetInputDirection({ -3.f,0.f });
		}

		pMovementComponent->Run(deltaSeconds);
	}
	else
	{
		pMovementComponent->SetRunning(false);
		pMovementComponent->SetInputDirection({ 0.f,0.f });
	}
}

void Client::Running::Exit()
{
	pAnimationComponent->SetPlayClip("ReadyToIdle");
}

void Client::Running::Remove()
{
}

Client::Running* Client::Running::Create()
{
	Running* running = new Running();
	running->_name = "RUNNING";

	return running;
}
