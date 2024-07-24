#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "Move.h"
#include "ClientFSMContainer.h"

void Client::Move::Enter()
{
	if(!pActor)
	{
		pActor				= _pOwnerComponent->GetOwner();
		pMovementComponent	= pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent	= pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent	= pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent		= pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	pBodyBoxComponent->SetSize({ 200.f, 600.f });
	bool isFlip = pAnimationComponent->IsFlip();
	Mathf::Vector2 direction = pMovementComponent->GetInputDirection();
	switch (isFlip)
	{
	case true:
		if (0.f < direction.x)
		{
			pAnimationComponent->SetPlayClip("ReadyToMove");
		}
		else if (0.f > direction.x)
		{
			pAnimationComponent->SetPlayClip("ReadyToBackMove");
		}
		break;
	case false:
		if (0.f > direction.x)
		{
			pAnimationComponent->SetPlayClip("ReadyToMove");
		}
		else if (0.f < direction.x)
		{
			pAnimationComponent->SetPlayClip("ReadyToBackMove");
		}
		break;
	}

}

void Client::Move::Execute(float deltaSeconds)
{
	bool isFlip = pAnimationComponent->IsFlip();
	Mathf::Vector2 direction = pMovementComponent->GetInputDirection();
	if (direction.y < 0)
	{
		pMovementComponent->Jump(deltaSeconds);
	}

	switch (isFlip)
	{
	case true:
		if (0.f > direction.x &&
			pAnimationComponent->IsClipEnd("ReadyToMove") &&
			pAnimationComponent->IsClipEnd("Move"))
		{
			pAnimationComponent->SetPlayClip("Move");
		}
		else if (0.f < direction.x &&
			pAnimationComponent->IsClipEnd("ReadyToBackMove") &&
			pAnimationComponent->IsClipEnd("BackMove"))
		{
			pAnimationComponent->SetPlayClip("BackMove");
		}
		break;
	case false:
		if (0.f < direction.x &&  
			pAnimationComponent->IsClipEnd("ReadyToMove") && 
			pAnimationComponent->IsClipEnd("Move"))
		{
			pAnimationComponent->SetPlayClip("Move");
		}
		else if (0.f > direction.x &&
			pAnimationComponent->IsClipEnd("ReadyToBackMove") &&
			pAnimationComponent->IsClipEnd("BackMove"))
		{
			pAnimationComponent->SetPlayClip("BackMove");
		}
		break;
	}

	if (pMovementComponent->IsJumping())
	{
		pAnimationComponent->SetPlayClip("Jump");
	}
	pMovementComponent->Move(deltaSeconds);

}

void Client::Move::Exit()
{
}

void Client::Move::Remove()
{
	for(auto& transit : _transitions)
	{
		SafeDelete(transit);
	}
}

Client::Move* Client::Move::Create()
{
	Move* move = new Move();
	move->_name = "MOVE";

	return move;
}
