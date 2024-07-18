#pragma once
#include "../../Engine/Headers/State.h"
namespace Core
{
	class Actor;
	class BoxComponent;
}

namespace Client
{
	class LowKick : public Core::State
	{
	protected:
		explicit LowKick() = default;
		virtual ~LowKick() = default;

	public:
		void Enter() override;
		void Execute(float deltaTime) override;
		void Exit() override;
		void Remove() override;

	public:
		static LowKick* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		::Core::BoxComponent* pBodyBoxComponent{ nullptr };
		::Core::BoxComponent* pFootBoxComponent{ nullptr };

	};
}