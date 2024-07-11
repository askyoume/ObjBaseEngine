#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"

#include "LowKick.h"
#include "Aoko.h"
#include "ClientFSMContainer.h"

void Client::LowKick::Enter()
{
	if(!pAoko)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
	}

	pAoko->SetPlayClip("LowKick");
}

void Client::LowKick::Execute(float deltaTime)
{
}

void Client::LowKick::Exit()
{
}

void Client::LowKick::Remove()
{
}

Client::LowKick* Client::LowKick::Create()
{
	return nullptr;
}
