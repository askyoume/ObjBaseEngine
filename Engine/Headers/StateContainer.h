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
		explicit StateContainer() DEFAULT;
		virtual ~StateContainer() DEFAULT;

	public:
		virtual void ContainStep() PURE;
		virtual void Update(float deltaTime) PURE;
		virtual void Remove() override PURE;

	public:
		void ChangeState(_pstring targetState);
		void SetInitialState(_pstring initialState);
		void AddState(State* pState);
		void SetOwner(StateComponent* pOwnerComponent) { _pOwnerComponent = pOwnerComponent; }
		StateComponent* GetOwnerComponent() const { return _pOwnerComponent; }

	protected:
		StateComponent*		_pOwnerComponent{ nullptr };
		State*				_previousState{ nullptr };
		State*				_currentState{ nullptr };
		State*				_initialState{ nullptr };
		StateMap			_states;
		PriorityStateList	_priorityStates;
	};
}