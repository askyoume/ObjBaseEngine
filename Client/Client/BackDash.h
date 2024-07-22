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
	class BackDash : public Core::State
	{
	protected:
		explicit BackDash() = default;
		virtual ~BackDash() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static BackDash* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTarget{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent* pBoxComponent{ nullptr };
	private:
		float DashTargetLocationX{ 0.f };
	};
}