#include "MainEntry.h"
#include "CoreManager.h"
#include "System.h"

void Game::MainEntry::Initialize(::Core::CoreManager::GameSetting _gameSetting)
{
	constexpr int SCREEN_START_LEFT = 10;
	constexpr int SCREEN_START_TOP = 10;

	const TCHAR* appName = TEXT("Test D2D FrameWork");

	WNDCLASS wndClass{};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = _gameSetting.hInstance;
	wndClass.hIcon = LoadIcon(_gameSetting.hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	if (_gameSetting.width <= 0 || _gameSetting.height <= 0)
	{
		_gameSetting.width = (float)_width;
		_gameSetting.height = (float)_height;
	}

	RECT rect
	{	
		SCREEN_START_LEFT, 
		SCREEN_START_TOP,
		SCREEN_START_LEFT + (LONG)_gameSetting.width, 
		SCREEN_START_TOP + (LONG)_gameSetting.height 
	};

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	_gameSetting.width = static_cast<float>(rect.right - rect.left);
	_gameSetting.height = static_cast<float>(rect.bottom - rect.top);

	_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, 
		(int)_gameSetting.width, 
		(int)_gameSetting.height, 
		NULL, NULL, _gameSetting.hInstance, NULL);

	ShowWindow(_hWnd, SW_NORMAL);
	UpdateWindow(_hWnd);

	_gameSetting.hWnd = _hWnd;

	_pSystem = Game::System::Create(_gameSetting);
}

int Game::MainEntry::MainLoop()
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

void Game::MainEntry::Release()
{
	if (_pSystem)
	{
		_pSystem->Release();
		_pSystem = nullptr;
	}
	//UnregisterClass(TEXT("Test D2D FrameWork"), _hInstance);
}

LRESULT Game::MainEntry::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
