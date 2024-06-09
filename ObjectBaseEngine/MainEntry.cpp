#include <cstdlib>

#include "MainEntry.h"
#include "CoreManager.h"
#include "System.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

constexpr int SCREEN_START_LEFT = 10;
constexpr int SCREEN_START_TOP = 10;
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR lpszCmdParam, 
	_In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(257);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpszCmdParam);

	Game::WinApp winApp;

	winApp.Initialize(hInstance);
	winApp.MainLoop();
	winApp.Release();
	
	_CrtDumpMemoryLeaks();


	return EXIT_SUCCESS;
}

void Game::WinApp::Initialize(HINSTANCE hInstance)
{
	_hInstance = hInstance;

	const TCHAR* appName = TEXT("Test D2D FrameWork");

	//Step 1: Registering the Window Class

	WNDCLASS wndClass{};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	RECT rect{ SCREEN_START_LEFT, SCREEN_START_TOP,
	SCREEN_START_LEFT + SCREEN_WIDTH, SCREEN_START_TOP + SCREEN_HEIGHT };

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(_hWnd, SW_NORMAL);
	UpdateWindow(_hWnd);

	_pSystem = Game::System::Create(hInstance, _hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	_pGameManager = Core::CoreManager::GetInstance();
}

int Game::WinApp::MainLoop()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;
			else
			{
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (!_pSystem->MainLoop())
				break;
		}
	}

    return 0;
}

void Game::WinApp::Release()
{
	if (_pSystem)
	{
		_pSystem->Release();
		_pSystem = nullptr;
	}
	//UnregisterClass(TEXT("Test D2D FrameWork"), _hInstance);
}

LRESULT Game::WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
