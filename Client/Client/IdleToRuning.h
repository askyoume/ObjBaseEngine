#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class IdleToRuning : public Core::StateTransition
	{
	protected:
		explicit IdleToRuning() DEFAULT;
		virtual ~IdleToRuning() DEFAULT;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToRuning* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}