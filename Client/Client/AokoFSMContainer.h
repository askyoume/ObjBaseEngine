#pragma once
#include "../../Engine/Headers/StateContainer.h"

namespace Client
{
	class AokoFSMContainer : public Core::StateContainer
	{
	protected:
		explicit AokoFSMContainer() DEFAULT;
		virtual ~AokoFSMContainer() DEFAULT;

	public:
		void ContainStep() override;
		void Update(float deltaTime) override;
		void Remove() override;

	public:
		static AokoFSMContainer* Create();
	};
}
