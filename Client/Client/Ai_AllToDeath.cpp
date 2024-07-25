#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/World.h"

#include "IPlayerInfo.h"
#include "Ai_AllToDeath.h"

bool Client::AI_AllToDeath::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pPlayerInfo = dynamic_cast<IPlayerInfo*>(pActor);
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	}

	if (0 >= pPlayerInfo->GetHP())
	{
		SetTargetState("AI_DEAD");
		return true;
	}

    return false;
}

void Client::AI_AllToDeath::Remove()
{
}

Client::AI_AllToDeath* Client::AI_AllToDeath::Create()
{
	return new AI_AllToDeath;
}
