#include "StateComponent.h"
#include "StateContainer.h"

bool Core::StateComponent::Initialize()
{
	return true;
}

void Core::StateComponent::BeginPlay()
{
}

void Core::StateComponent::TickComponent(_float deltaTime)
{
	_pContainer->Update(deltaTime);
}

void Core::StateComponent::EndPlay()
{
}

void Core::StateComponent::Remove()
{
	SafeDelete(_pContainer);
}
