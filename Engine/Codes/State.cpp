#include "State.h"
#include "StateTransition.h"

bool Core::State::IsPriorityState(State* pFindTarget)
{
	for(auto& pState : _states)
	{
		if(pState == pFindTarget)
		{
			return true;
		}
	}

	return false;
}

bool Core::State::TransitionPoint(_pstring targetState)
{
	for (auto& pTransition : _transitions)
	{
		if (pTransition->ShouldTransition())
		{
			pTransition->SetTargetState(targetState);
			return true;
		}
	}

	return false;
}

void Core::State::BindState(State* pState)
{
	_states.push_back(pState);
}

void Core::State::SetOwnerComponent(StateComponent* pStateComponent)
{
	_pOwnerComponent = pStateComponent;
}

void Core::State::AddTransition(StateTransition* pTransition)
{
	pTransition->SetOwnerComponent(_pOwnerComponent);
	_transitions.push_back(pTransition);
}

