#pragma once
#include "Core.h"
#include "Client_Macro.h"

namespace Core
{
	class CoreManager;
}

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
		bool Initialize(HINSTANCE hInstance, HWND hWnd, float width, float height);
		void Remove() override;

	public:
		static System* Create(HINSTANCE hInstance, HWND hWnd, float width, float height);

	private:
		::Core::CoreManager* _pCoreMgr{ nullptr };
	};
}