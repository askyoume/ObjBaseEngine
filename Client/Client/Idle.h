#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
};

namespace Client
{
	class Idle : public Core::State
	{
	protected:
		explicit Idle() DEFAULT;
		virtual ~Idle() DEFAULT;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static Idle* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
	};
}