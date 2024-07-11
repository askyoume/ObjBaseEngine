#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"

#include "Idle.h"
#include "Character.h"
#include "Aoko.h"
#include "ClientFSMContainer.h"

void Client::Idle::Enter()
{
	if(!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	if(pAnimationComponent->IsClipEnd("ReadyToIdle"))
		pAnimationComponent->SetPlayClip("Idle");
}

void Client::Idle::Execute(float deltaTime)
{
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
