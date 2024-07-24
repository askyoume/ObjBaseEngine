#pragma once
#include "../../Engine/Headers/StateContainer.h"

namespace Client
{
	class ClientFSMContainer : public Core::StateContainer
	{
	protected:
		explicit ClientFSMContainer() = default;
		virtual ~ClientFSMContainer() = default;

	public:
		void ContainStep() override;
		void Update(float deltaSeconds) override;
		void Remove() override;

	public:
		static ClientFSMContainer* Create();
	};
}
