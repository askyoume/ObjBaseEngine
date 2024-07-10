#include "../../Engine/Headers/StateComponent.h"

#include "Runing.h"
#include "Aoko.h"
#include "AokoFSMContainer.h"

void Client::Runing::Enter()
{
	if(_pOwnerComponent)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
		pAoko->SetPlayClip("Runing");
	}
}

void Client::Runing::Execute(float deltaTime)
{
}

void Client::Runing::Exit()
{
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
