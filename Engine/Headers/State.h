#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class State abstract : public Core
	{
	protected:
		explicit State() = default;
		virtual ~State() = default;

	public:
		virtual void Enter() PURE;
		virtual void Execute(float deltaSeconds) PURE;
		virtual void Exit() PURE;
		virtual void Remove() override PURE;

	public:
		bool IsPriority() const { return _isPriority; }
		bool IsEndState() const { return _isEndState; }
		bool IsExit() const { return _isExit; }
		void SetEndState(bool isEndState) { _isEndState = isEndState; }
		void SetPriority(bool isPriority) { _isPriority = isPriority; }
		void SetExit(bool isExit) { _isExit = isExit; }
		void SetPreviousStateName(_pstring previousStateName) { _previousStateName = previousStateName; }

	public:
		bool IsPriorityState(State* pFindTarget);
		bool TransitionPoint(_pstring targetState);

	public:
		void BindState(State* pState);
		void SetOwnerComponent(StateComponent* pStateComponent);
		void AddTransition(StateTransition* pTransition);
		std::vector<StateTransition*> GetTransitions() const { return _transitions; }

	public:
		_pstring GetName() const { return _name; }

	protected:
		bool						  _isPriority{ false };
		bool						  _isExit{ false };
		bool						  _isEndState{ false };
		_pstring                      _previousStateName{ nullptr };
		_pstring					  _name{ nullptr };
		StateComponent*				  _pOwnerComponent{ nullptr };
		std::vector<StateTransition*> _transitions;
		std::vector<State*>			  _states;
	};
}