#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include "Client_Macro.h"
#include "../../Engine/Headers/CoreManager.h"

namespace Core
{
	class World;
}

namespace Game
{
	CLIENTCLASS()
	class MainEntry abstract
	{
	public:
		MainEntry() DEFAULT;
		~MainEntry() DEFAULT;

	public:
		virtual void CreateWorld() PURE; //이게 클라이언트에서 상속받아서 사용시에 월드를 강제로 생성하게 하기 위한 함수
		Core::World* LoadWorld() { return _pWorld; }

		void Initialize(::Core::CoreManager::GameSetting gameSetting);
		int MainLoop();
		void Release();

		HINSTANCE GetInstance() const { return _hInstance; }
		HWND GetHWnd() const { return _hWnd; }

		const int GetWidth() const { return _width; }
		const int GetHeight() const { return _height; }

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		Core::World* _pWorld{ nullptr };

	private:
		HINSTANCE _hInstance{};
		HWND _hWnd{};
		System* _pSystem{ nullptr };
		int _width{ 1024 };
		int _height{ 768 };
	};
}