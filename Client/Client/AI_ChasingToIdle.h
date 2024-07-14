#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class AI_ChasingToIdle : public Core::StateTransition
	{
	protected:
		explicit AI_ChasingToIdle() = default;
		virtual ~AI_ChasingToIdle() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static AI_ChasingToIdle* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}