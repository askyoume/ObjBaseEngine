#pragma once
#include "../../Engine/Headers/StateContainer.h"

namespace Client
{
	class ClientFSMContainer : public Core::StateContainer
	{
	protected:
		explicit ClientFSMContainer() DEFAULT;
		virtual ~ClientFSMContainer() DEFAULT;

	public:
		void ContainStep() override;
		void Update(float deltaTime) override;
		void Remove() override;

	public:
		static ClientFSMContainer* Create();
	};
}
