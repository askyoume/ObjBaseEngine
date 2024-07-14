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
	class AI_Idle : public Core::State
	{
	protected:
		explicit AI_Idle() = default;
		virtual ~AI_Idle() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static AI_Idle* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}