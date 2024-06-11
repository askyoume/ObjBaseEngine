#include <cstdlib>

#include "../../Engine/Headers/Core_Define.h"
#include "../../ObjectBaseEngine/System.h"
#include "../../Engine/Headers/CoreManager.h"
//#include "../../Engine/Headers/World.h"
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

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR lpszCmdParam, 
	_In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(257);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpszCmdParam);

	Client::ClientGame winApp;
	winApp.CreateWorld();
    ::Core::CoreManager::GameSetting gameSetting{};

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
