#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "AirLaunch.h"
#include "ClientFSMContainer.h"

#undef min

void Client::AirLaunch::Enter()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
	}

	//std::cout << "AirLaunchEnter" << std::endl;

	if (pAnimationComponent->IsClipEnd("AutoComboAirLaunch"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_BLOCK);
		pAnimationComponent->SetPlayClip("AutoComboAirLaunch");
	}
}

void Client::AirLaunch::Execute(float deltaSeconds)
{
	if (pAnimationComponent->IsClipEnd("AutoComboAirLaunch"))
	{
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::AirLaunch::Exit()
{
	if(pAnimationComponent->IsClipEnd("AutoComboAirLaunch"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	}
}

void Client::AirLaunch::Remove()
{
	for (auto& transit : _transitions)
	{
		SafeDelete(transit);
	}

	_transitions.clear();
}

Client::AirLaunch* Client::AirLaunch::Create()
{
	AirLaunch* pInstance = new AirLaunch();
	pInstance->_name = "AirLaunch";

	return pInstance;
}
