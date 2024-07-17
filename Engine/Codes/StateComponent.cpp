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

void Core::StateComponent::ChangeState(_pstring targetState)
{
	_pContainer->ChangeState(targetState);
}

_pstring Core::StateComponent::GetCurrentStateName() const
{
	return _pContainer->GetCurrentStateName();
}

_pstring Core::StateComponent::GetPreviousStateName() const
{
	return _pContainer->GetPreviousStateName();
}
