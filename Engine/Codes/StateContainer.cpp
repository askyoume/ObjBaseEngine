#include "StateContainer.h"
#include "State.h"
#include "StateTransition.h"

void Core::StateContainer::Update(float deltaSeconds)
{
	if (!_currentState)
	{
		if(!_initialState)
		return;

		_pstring initialState = _initialState->GetName();
		ChangeState(initialState);
		return;
	}

	_currentState->Execute(deltaSeconds);
	_previousState = _currentState;

	for(auto& pTransition : _currentState->GetTransitions())
	{
		if (pTransition->ShouldTransition())
		{
			_pstring targetState = pTransition->GetTargetState();
			ChangeState(targetState);
			return;
		}
	}

	for (auto& pState : _priorityStates)
	{
		if (pState->TransitionPoint(_currentState->GetName()))
		{
			ChangeState(pState->GetName());
			return;
		}
	}

	if (_previousState == _currentState)
	{
		if(_currentState == _initialState)
		{
			return;
		}

		if (!_initialState)
		{
			return;
		}

		for(auto& pTransition : _initialState->GetTransitions())
		{
			if (!pTransition->ShouldTransition())
			{
				_pstring initialState = _initialState->GetName();
				ChangeState(initialState);
				return;
			}
		}
	}
}

void Core::StateContainer::Remove()
{
	for (auto& state : _states)
	{
		SafeDelete(state.second);
	}
}

void Core::StateContainer::ForceCheckTransition(_pstring targetState)
{
	size_t transitionSize = _states[targetState]->GetTransitions().size();

	if (transitionSize == 0)
	{
		return;
	}

	for (size_t i = 0; i < transitionSize; ++i)
	{
		if (_states[targetState]->GetTransitions()[i]->ShouldTransition())
		{
			ChangeState(targetState);
			return;
		}
	}
}

void Core::StateContainer::ChangeState(_pstring targetState)
{
	_pstring previousState{ "None" }; 
	if(_currentState)
	{
		previousState = _currentState->GetName();
		_currentState->Exit();
	}

	auto pFindState = _states.find(targetState);
	if (pFindState != _states.end())
	{
		pFindState->second->SetPreviousStateName(previousState);
		_currentState = pFindState->second;
		_currentState->Enter();
	}
	else
	{
		return;
	}
}

void Core::StateContainer::SetInitialState(_pstring initialState)
{
	auto pFindState = _states.find(initialState);
	if (pFindState != _states.end())
	{
		_initialState = pFindState->second;
	}
	else
	{
		return;
	}
}

void Core::StateContainer::AddState(State* pState)
{
	_states.insert(std::make_pair(pState->GetName(), pState));
	pState->SetOwnerComponent(_pOwnerComponent);
	if (pState->IsPriority())
	{
		_priorityStates.push_back(pState);
	}
}

_pstring Core::StateContainer::GetCurrentStateName() const
{
	if(!_currentState)
	{
		return "None";
	}

	return _currentState->GetName();
}

_pstring Core::StateContainer::GetPreviousStateName() const
{
	if(!_previousState)
	{
		return "None";
	}

	return _previousState->GetName();
}

