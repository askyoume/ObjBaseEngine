#include "../../Engine/Headers/StateComponent.h"

#include "Idle.h"
#include "Aoko.h"
#include "AokoFSMContainer.h"

void Client::Idle::Enter()
{
	if(_pOwnerComponent)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
		pAoko->SetPlayClip("Idle");
	}
}

void Client::Idle::Execute(float deltaTime)
{
}

void Client::Idle::Exit()
{
}

void Client::Idle::Remove()
{
}

Client::Idle* Client::Idle::Create()
{
	Idle* idle = new Idle();
	idle->_name = "IDLE";

    return idle;
}
