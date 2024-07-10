#include "Aoko.h"
#include "IdleToRuning.h"
#include "../../Engine/Headers/StateContainer.h"
#include "../../Engine/Headers/StateComponent.h"

bool Client::IdleToRuning::ShouldTransition()
{
	if(!pAoko)
	{
		pAoko = static_cast<Aoko*>(_pOwnerComponent->GetOwner());
	}

	Mathf::Vector2 _direction = pAoko->GetDirection();
	if (0.5f < _direction.x || -0.5 > _direction.x)
	{
		SetTargetState("RUNING");
		std::cout << _direction.x << std::endl;
		return true;
	}

	return false;
}

void Client::IdleToRuning::Remove()
{
}

Client::IdleToRuning* Client::IdleToRuning::Create()
{
	IdleToRuning* pTransit = new IdleToRuning();
	return pTransit;
}
