#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
	class AnimationComponent;
	class BoxComponent;
	class InputComponent;
}

namespace Client
{
	class StartToAirLaunch : public Core::StateTransition
	{
	protected:
		explicit StartToAirLaunch() = default;
		virtual ~StartToAirLaunch() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static StartToAirLaunch* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
		::Core::BoxComponent* pFootBoxComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::InputComponent* pInputComponent{ nullptr };
	};
}