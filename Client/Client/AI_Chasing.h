#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class MovementComponent;
};

namespace Client
{
	class AI_Chasing : public Core::State
	{
	protected:
		explicit AI_Chasing() = default;
		virtual ~AI_Chasing() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static AI_Chasing* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
	};
}