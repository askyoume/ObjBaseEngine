#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"

#include "Idle.h"
#include "ClientFSMContainer.h"

void Client::Idle::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
	}

	if (pAnimationComponent->IsClipEnd("ReadyToIdle") && 
		pAnimationComponent->IsClipEnd("Idle") &&
		pAnimationComponent->IsClipEnd("Jump") &&
		pAnimationComponent->IsClipEnd("MiddleKick"))
	{
		pAnimationComponent->SetPlayClip("Idle");
	}
}

void Client::Idle::Execute(float deltaTime)
{
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (_direction.y < 0)
	{
		//_pOwnerComponent->ChangeState("JUMP");
		pMovementComponent->Jump(deltaTime);
	}

	if (pMovementComponent->IsJumping())
	{
		std::cout << "Jump" << (pMovementComponent->IsJumping()? "true" : "false")<< std::endl;
		pAnimationComponent->SetPlayClip("Jump");
	}
	else if (pAnimationComponent->IsClipEnd("ReadyToIdle") && 
		pAnimationComponent->IsClipEnd("Idle") &&
		pAnimationComponent->IsClipEnd("Jump"))
	{
		pAnimationComponent->SetPlayClip("Idle");
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
