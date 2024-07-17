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
	class IdleToKick : public Core::StateTransition
	{
	protected:
		explicit IdleToKick() = default;
		virtual ~IdleToKick() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToKick* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::InputComponent*		pInputComponent{ nullptr };
		::Core::BoxComponent*		pBoxComponent{ nullptr };
	};
}