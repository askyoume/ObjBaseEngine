#pragma once
#include "../../Engine/Headers/Core.h"
#include "Client_Macro.h"
#include "../../Engine/Headers/CoreManager.h"

namespace Game
{
	class System : public Core::Core
	{
	private:
		explicit System() DEFAULT;
		virtual ~System() DEFAULT;
		DENY_COPY(System)

	public:
		bool MainLoop();

	private:
		bool Initialize(::Core::CoreManager::GameSetting gameSetting);
		void Remove() override;

	public:
		static System* Create(::Core::CoreManager::GameSetting gameSetting);

	private:
		::Core::CoreManager* _pCoreMgr{ nullptr };
	};
}