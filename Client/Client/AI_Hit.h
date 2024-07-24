#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
	class MovementComponent;
};

namespace Client
{
	class AI_Hit : public Core::State
	{
	protected:
		explicit AI_Hit() = default;
		virtual ~AI_Hit() = default;

	public:
		void Enter() override;
		void Execute(float deltaSeconds) override;
		void Exit() override;
		void Remove() override;

	public:
		static AI_Hit* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}