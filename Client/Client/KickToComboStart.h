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
	class KickToComboStart : public Core::StateTransition
	{
	protected:
		explicit KickToComboStart() = default;
		virtual ~KickToComboStart() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static KickToComboStart* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::InputComponent* pInputComponent{ nullptr };
		::Core::BoxComponent* pBoxComponent{ nullptr };
	};
}