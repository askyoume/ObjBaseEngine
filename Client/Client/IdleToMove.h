#pragma once
#include "../../Engine/Headers/StateTransition.h"

namespace Core
{
	class Actor;
	class MovementComponent;
}

namespace Client
{
	class IdleToMove : public Core::StateTransition
	{
	protected:
		explicit IdleToMove() DEFAULT;
		virtual ~IdleToMove() DEFAULT;

	public:
		bool ShouldTransition() override;
		void Remove() override;

	public:
		static IdleToMove* Create();

	private:
		::Core::Actor* pActor{ nullptr };
		::Core::MovementComponent* pMovementComponent{ nullptr };
	};
}