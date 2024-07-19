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
	class IdleToMiddleKick : public Core::StateTransition
	{
	protected:
		explicit IdleToMiddleKick() = default;
		virtual ~IdleToMiddleKick() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToMiddleKick* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::InputComponent*		pInputComponent{ nullptr };
		::Core::BoxComponent*		pBoxComponent{ nullptr };
	};
}