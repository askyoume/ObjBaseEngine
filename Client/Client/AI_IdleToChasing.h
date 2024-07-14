#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class AI_IdleToChasing : public Core::StateTransition
	{
	protected:
		explicit AI_IdleToChasing() = default;
		virtual ~AI_IdleToChasing() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static AI_IdleToChasing* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}