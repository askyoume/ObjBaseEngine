#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../ObjectBaseEngine/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"

#include "Runing.h"
#include "Aoko.h"
#include "ClientFSMContainer.h"

void Client::Runing::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
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

	pAnimationComponent->SetPlayClip("ReadyToRuning");
}

void Client::Runing::Execute(float deltaTime)
{
	if(pAnimationComponent->IsClipEnd("ReadyToRuning"))
	{
		pAnimationComponent->SetPlayClip("Runing");
	}
;
	Mathf::Vector2 _direction = pMovementComponent->GetInputDirection();
	pMovementComponent->Move(deltaTime);
}

void Client::Runing::Exit()
{
	pAnimationComponent->SetPlayClip("ReadyToIdle");
}

void Client::Runing::Remove()
{
}

Client::Runing* Client::Runing::Create()
{
	Runing* runing = new Runing();
	runing->_name = "RUNING";

	return runing;
}
