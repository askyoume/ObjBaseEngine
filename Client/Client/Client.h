#pragma once

#include "../../ObjectBaseEngine/Client_Macro.h"
#include "../../ObjectBaseEngine/MainEntry.h"

namespace Core
{
	class CoreManager;
	class World;
}

namespace Client
{
	class ClientGame : public Game::MainEntry
	{
	public:
		ClientGame() DEFAULT;
		~ClientGame() DEFAULT;

		void CreateWorld() override;
	};
}