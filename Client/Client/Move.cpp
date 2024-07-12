#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../ObjectBaseEngine/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"

#include "Move.h"
#include "ClientFSMContainer.h"

void Client::Move::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (0.f < _direction.x)
	{
		pAnimationComponent->SetPlayClip("ReadyToMove");
	}
	else if (0.f > _direction.x)
	{
		pAnimationComponent->SetPlayClip("ReadyToBackMove");
	}
}

void Client::Move::Execute(float deltaTime)
{
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	if (0.f < _direction.x &&  
		pAnimationComponent->IsClipEnd("ReadyToMove") && 
		pAnimationComponent->IsClipEnd("Move"))
	{
		pAnimationComponent->SetPlayClip("Move");
	}
	else if (0.f > _direction.x &&
		pAnimationComponent->IsClipEnd("ReadyToBackMove") &&
		pAnimationComponent->IsClipEnd("BackMove"))
	{
		pAnimationComponent->SetPlayClip("BackMove");
	}

	pMovementComponent->Move(deltaTime);
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
