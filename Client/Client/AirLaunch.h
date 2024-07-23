#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class MovementComponent;
	class InputComponent;
	class AnimationComponent;
	class BoxComponent;
}

namespace Client
{
	class AirLaunch : public Core::State
	{
	protected:
		explicit AirLaunch() = default;
		virtual ~AirLaunch() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static AirLaunch* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::Actor*				pTargetActor{ nullptr };
		::Core::InputComponent*		pInputComponent{ nullptr };
		::Core::MovementComponent*	pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent*		pBodyBoxComponent{ nullptr };
		::Core::BoxComponent*		pFootBoxComponent{ nullptr };
	};
}