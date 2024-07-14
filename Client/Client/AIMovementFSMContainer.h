#pragma once
#include "../../Engine/Headers/StateContainer.h"

namespace Client
{
	class AIMovementFSMContainer : public Core::StateContainer
	{
	protected:
		explicit AIMovementFSMContainer() = default;
		virtual ~AIMovementFSMContainer() = default;

	public:
		void ContainStep() override;
		void Update(float deltaTime) override;
		void Remove() override;

	public:
		static AIMovementFSMContainer* Create();
	};
}