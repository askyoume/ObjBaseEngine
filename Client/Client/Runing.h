#pragma once
#include "../../Engine/Headers/State.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class Actor;
	class MovementComponent;
	class AnimationComponent;
	class BoxComponent;
}

namespace Client
{
	class Running : public Core::State
	{
	protected:
		explicit Running() = default;
		virtual ~Running() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Running* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent* pBoxComponent{ nullptr };
	};
}