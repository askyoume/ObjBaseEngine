#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "StartToAirLaunch.h"

bool Client::StartToAirLaunch::ShouldTransition()
{
	if (!pActor)
	{
		pActor = _pOwnerComponent->GetOwner();
		pMovementComponent = pActor->GetComponent<::Core::MovementComponent>("MovementComponent");
		pAnimationComponent = pActor->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		pFootBoxComponent = pActor->GetComponent<::Core::BoxComponent>("FootBoxComponent");
		pInputComponent = pActor->GetComponent<::Core::InputComponent>("InputComponent");
	}

	std::cout << "StartToAirLaunch" << std::endl;

    if(pAnimationComponent->IsClipEnd("AutoComboStart"))
	{
		if (pInputComponent->IsKeyEventTriggeredLessTime(DIK_A, InputType::PRESS, 0.28f))
		{
			if (pAnimationComponent->IsFlip())
			{
				pFootBoxComponent->SetAddOffset({ -60.f, 0.f });
			}
			else
			{
				pFootBoxComponent->SetAddOffset({ 60.f, 0.f });
			}
			pFootBoxComponent->SetSize({ 150.f, 350.f });
			pFootBoxComponent->SetCollisionType(Collision::COLLISION_BLOCK);
			//_pOwnerComponent->ChangeState("AirLaunch");
			SetTargetState("AirLaunch");
			return true;
		}
	}

	return false;
}

void Client::StartToAirLaunch::Remove()
{
}

Client::StartToAirLaunch* Client::StartToAirLaunch::Create()
{
    return new StartToAirLaunch;
}
