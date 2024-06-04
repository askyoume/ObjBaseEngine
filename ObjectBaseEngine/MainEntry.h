#pragma once

#include <sdkddkver.h>
#include <windows.h>
#include "Client_Macro.h"

namespace Core
{
	class CoreManager;
}

namespace Game
{
	CLIENTCLASS()
	class WinApp
	{
	public:
		WinApp() DEFAULT;
		~WinApp() DEFAULT;

		void Initialize(HINSTANCE hInstance);

		int MainLoop();

		void Release();

		HINSTANCE GetInstance() const { return _hInstance; }
		HWND GetHWnd() const { return _hWnd; }

		const int GetWidth() const { return _width; }
		const int GetHeight() const { return _height; }

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE _hInstance{};
		HWND _hWnd{};
		System* _pSystem{ nullptr };
		Core::CoreManager* _pGameManager{ nullptr };
		int _width{ 1024 };
		int _height{ 768 };
	};
}