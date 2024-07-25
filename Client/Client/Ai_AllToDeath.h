#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
};

namespace Client
{
	Interface IPlayerInfo;
	class AI_AllToDeath : public Core::StateTransition
	{
	protected:
		explicit AI_AllToDeath() = default;
		virtual ~AI_AllToDeath() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static AI_AllToDeath* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::AnimationComponent* pAnimationComponent{ nullptr };
		IPlayerInfo* pPlayerInfo{ nullptr };
	};
}