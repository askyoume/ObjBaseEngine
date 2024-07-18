#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"

#include "Runing.h"
#include "ClientFSMContainer.h"

void Client::Running::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
	}

	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (_direction.x > 0)
	{
		pAnimationComponent->SetFlip(false);
	}
	else
	{
		pAnimationComponent->SetFlip(true);
	}

	pAnimationComponent->SetPlayClip("ReadyToRunning");
	pBoxComponent->SetSize({ 280.f, 400.f });
}

void Client::Running::Execute(float deltaTime)
{
	if(!pMovementComponent->IsJumping() &&
		pAnimationComponent->IsClipEnd("ReadyToRunning") &&
		pAnimationComponent->IsClipEnd("Running"))
	{
		pMovementComponent->SetRunning(true);
		pAnimationComponent->SetPlayClip("Running");
	}

	pMovementComponent->Run(deltaTime);
}

void Client::Running::Exit()
{
	pAnimationComponent->SetPlayClip("ReadyToIdle");
	pMovementComponent->SetRunning(false);
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
