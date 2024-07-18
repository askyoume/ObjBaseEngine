#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class IdleToRunning : public Core::StateTransition
	{
	protected:
		explicit IdleToRunning() = default;
		virtual ~IdleToRunning() = default;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToRunning* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}