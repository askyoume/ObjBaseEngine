#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class AI_IdleToAttack : public Core::StateTransition
	{
	protected:
		explicit AI_IdleToAttack() = default;
		virtual ~AI_IdleToAttack() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static AI_IdleToAttack* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}