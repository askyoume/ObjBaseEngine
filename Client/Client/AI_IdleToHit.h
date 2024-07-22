#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
	class MovementComponent;
}

namespace Client
{
	class AI_IdleToHit : public Core::StateTransition
	{
	protected:
		explicit AI_IdleToHit() = default;
		virtual ~AI_IdleToHit() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static AI_IdleToHit* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}