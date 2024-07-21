#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/MovementComponent.h" //temp
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BoxComponent.h"

#include "AutoComboStart.h"
#include "ClientFSMContainer.h"

void Client::AutoComboStart::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pTargetActor = ::Core::CoreManager::GetInstance()->GetWorld()->FindActor("Neko");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pBodyBoxComponent = pActor->GetComponent<::Core::BoxComponent>("BodyBoxComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
	}

	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		pFootBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
		pAnimationComponent->SetPlayClip("AutoComboStart");
	}
}

void Client::AutoComboStart::Execute(float deltaTime)
{
	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		_pOwnerComponent->ChangeState("IDLE");
	}
}

void Client::AutoComboStart::Exit()
{
	if (pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
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
