#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/StateTransition.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"

#include "Idle.h"
#include "Character.h"
#include "Aoko.h"
#include "AokoFSMContainer.h"

void Client::Idle::Enter()
{
	if(!pAoko)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
	}

	//if (!pCharacter)
	//{
	//	::Core::CoreManager* pCoreManager = ::Core::CoreManager::GetInstance();
	//	pCharacter = dynamic_cast<Character*>(pCoreManager->GetWorld()->FindActor("Character"));
	//}

	::Core::AnimationComponent* pAnimationComponent = 
		pAoko->GetComponent<::Core::AnimationComponent>("AnimationComponent");

	if(pAnimationComponent->IsClipEnd("ReadyToIdle"))
		pAoko->SetPlayClip("Idle");
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
