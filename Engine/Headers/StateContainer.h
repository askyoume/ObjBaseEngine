#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class StateContainer abstract : public Core
	{
	public:
		using StateMap = std::unordered_map<_pstring, State*>;
		using PriorityStateList = std::vector<State*>;

	protected:
		explicit StateContainer() = default;
		virtual ~StateContainer() = default;

	public:
		virtual void ContainStep() PURE;
		virtual void Update(float deltaSeconds) PURE;
		virtual void Remove() override PURE;

	public:
		void ForceCheckTransition(_pstring targetState);
		void ChangeState(_pstring targetState);
		void SetInitialState(_pstring initialState);
		void AddState(State* pState);
		void SetOwner(StateComponent* pOwnerComponent) { _pOwnerComponent = pOwnerComponent; }
		StateComponent* GetOwnerComponent() const { return _pOwnerComponent; }

	public:
		//use Debugging
		_pstring GetCurrentStateName() const;
		_pstring GetPreviousStateName() const;

	protected:
		StateComponent*		_pOwnerComponent{ nullptr };
		State*				_previousState{ nullptr };
		State*				_currentState{ nullptr };
		State*				_initialState{ nullptr };
		StateMap			_states;
		PriorityStateList	_priorityStates;
	};
}