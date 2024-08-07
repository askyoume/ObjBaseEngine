﻿#include <cstdlib>

#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/System.h"
#include "../../Engine/Headers/CoreManager.h"

#include "Client.h"
#include "TestActor.h"
#include "ClientWorld.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR lpszCmdParam, 
	_In_ int nCmdShow)
{
	_CrtSetBreakAlloc(0); //메모리 누수가 발생한 라인을 찾기 위한 코드 -> 디버그 창을 유심히 보면 라인값이 출력됨.

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpszCmdParam);

	Client::ClientGame winApp;

	winApp.CreateWorld();

    ::Core::CoreManager::GameSetting gameSetting{};

	gameSetting.title = TEXT("MELTY BLOOD - Q2_Project Create by Hero.P");
    gameSetting.hInstance = hInstance;
	gameSetting.pWorld = winApp.LoadWorld();
    gameSetting.width = SCREEN_WIDTH;
    gameSetting.height = SCREEN_HEIGHT;
    gameSetting.renderGroupSize = 1;
    gameSetting.maxSoundGroup = 1;
    gameSetting.levelSize = 1;
    gameSetting.layerSize = 5;

	winApp.Initialize(gameSetting);
	winApp.MainLoop();
	winApp.Release();
	
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}

void Client::ClientGame::CreateWorld()
{
	_pWorld = Client::ClientWorld::Create();
}
