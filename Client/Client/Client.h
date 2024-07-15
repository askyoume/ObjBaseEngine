#pragma once

#include "../../Engine/Headers/Client_Macro.h"
#include "../../Engine/Headers/MainEntry.h"

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
		ClientGame() = default;
		~ClientGame() = default;

		void CreateWorld() override;
	};
}