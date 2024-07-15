#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class StateTransition abstract : public Core
	{
	protected:
		explicit StateTransition() = default;
		virtual ~StateTransition() = default;
	public:
		virtual bool ShouldTransition() PURE;
		virtual void Remove() override PURE;

	public:
		void SetTargetState(_pstring targetState) { _targetState = targetState; }
		void SetOwnerComponent(StateComponent* pOwnerComponent) { _pOwnerComponent = pOwnerComponent; }
		_pstring GetTargetState() const { return _targetState; }

	protected:
		_pstring		_targetState;
		StateComponent*	_pOwnerComponent{ nullptr };
	};
}