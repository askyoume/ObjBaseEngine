#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "Idle.h"
#include "ClientFSMContainer.h"

void Client::Idle::Enter()
{
	if(!pActor)
	{
		pActor				= _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent	= pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pBodyBoxComponent	= pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent	= pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent		= pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	if (pAnimationComponent->IsFrameEnd() && 
		pMovementComponent->IsGrounded())
	{
		pAnimationComponent->SetPlayClip("Idle");
	}

	pBodyBoxComponent->SetSize({ 150.f, 600.f });
}

void Client::Idle::Execute(float deltaSeconds)
{
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (_direction.y < 0)
	{
		pMovementComponent->Move(deltaSeconds);
		pMovementComponent->Jump(deltaSeconds);
	}

	if (pMovementComponent->IsJumping())
	{
		pAnimationComponent->SetPlayClip("Jump");
	}
	else if (pAnimationComponent->IsClipEnd("JumpDownKick") && 
			 pAnimationComponent->IsFrameEnd() &&
			 pMovementComponent->IsGrounded())
	{
		pAnimationComponent->SetPlayClip("Idle");
	}

	if (pAnimationComponent->IsFrameEnd())
	{
		pMovementComponent->SetInputDirectionY(0.f);
	}
}

void Client::Idle::Exit()
{
}

void Client::Idle::Remove()
{
	for(auto& transit : _transitions)
	{
		SafeDelete(transit);
	}
}

Client::Idle* Client::Idle::Create()
{
	Idle* idle = new Idle();
	idle->_name = "IDLE";

    return idle;
}