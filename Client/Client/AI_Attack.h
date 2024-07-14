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
	class AI_Attack : public Core::State
	{
	protected:
		explicit AI_Attack() = default;
		virtual ~AI_Attack() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static AI_Attack* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}