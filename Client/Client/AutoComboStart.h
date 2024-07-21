#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
	class BoxComponent;
}

namespace Client
{
	class AutoComboStart : public Core::State
	{
	protected:
		explicit AutoComboStart() = default;
		virtual ~AutoComboStart() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static AutoComboStart* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::Actor* pTargetActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent* pBodyBoxComponent{ nullptr };
		::Core::BoxComponent* pFootBoxComponent{ nullptr };
	};
}