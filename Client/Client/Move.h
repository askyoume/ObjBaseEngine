#pragma once
#include "../../Engine/Headers/State.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class Actor;
	class InputComponent;
	class MovementComponent;
	class AnimationComponent;
	class BoxComponent;
}

namespace Client
{
	class Move : public Core::State
	{
	protected:
		explicit Move() = default;
		virtual ~Move() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Move* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::InputComponent*		pInputComponent{ nullptr };
		::Core::MovementComponent*	pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent*		pBodyBoxComponent{ nullptr };
		::Core::BoxComponent*		pFootBoxComponent{ nullptr };

	};
}