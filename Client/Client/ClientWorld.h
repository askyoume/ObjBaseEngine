#pragma once
#include "../../ObjectBaseEngine/Client_Macro.h"
#include "../../Engine/Headers/World.h"

namespace Core
{
	class CoreManager;
}

namespace Client
{
	class ClientWorld : public Core::World
	{
	private:
		explicit ClientWorld() DEFAULT;
		virtual ~ClientWorld() DEFAULT;

	public:
		static ClientWorld* Create() { return new ClientWorld; }
		bool BeginPlay() override;
	};
}