#pragma once
#include "../../Engine/Headers/State.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class Actor;
	class MovementComponent;
	class AnimationComponent;
}

namespace Client
{
	class Runing : public Core::State
	{
	protected:
		explicit Runing() DEFAULT;
		virtual ~Runing() DEFAULT;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Runing* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		bool isRuning{ false };
		float _elapsedTime{ 0.f };
		float _runSpeed{ 5.f };
	};
}