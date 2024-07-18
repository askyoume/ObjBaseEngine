#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
	class MovementComponent;
	class BoxComponent;
};

namespace Client
{
	class Idle : public Core::State
	{
	protected:
		explicit Idle() = default;
		virtual ~Idle() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Idle* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::MovementComponent*	pMovementComponent{ nullptr };
		::Core::BoxComponent*		pBoxComponent{ nullptr };
	};
}