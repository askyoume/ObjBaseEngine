#pragma once
#include "../../Engine/Headers/State.h"

namespace Core
{
	class Actor;
	class BoxComponent;
	class AnimationComponent;
};

namespace Client
{
	class AI_Dead : public Core::State
	{
	protected:
		explicit AI_Dead() = default;
		virtual ~AI_Dead() = default;

	public:
		void Enter() override;
		void Execute(float deltaSeconds) override;
		void Exit() override;
		void Remove() override;

	public:
		static AI_Dead* Create();

	private:
		::Core::Actor*				pActor{ nullptr };
		::Core::BoxComponent*		pBoxComponent{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
	};
}