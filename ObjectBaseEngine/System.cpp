#include "System.h"
#include "CoreManager.h"
#include "Core_Function.h"
//test code
#include "World.h"
#include "Actor.h"
#include "TestActor.h"

bool Game::System::MainLoop()
{
    if (!_pCoreMgr->IsEndPlay())
	{
		_pCoreMgr->Tick();
        _pCoreMgr->Fixed(50);
        _pCoreMgr->Render();
		_pCoreMgr->EndPlay();

        return true;
	}
    else
        return false;
}

bool Game::System::Initialize(HINSTANCE hInstance, HWND hWnd, float width, float height)
{
    ::Core::CoreManager::GameSetting gameSetting{};

    gameSetting.hInstance = hInstance;
    gameSetting.hWnd = hWnd;
    gameSetting.width = width;
    gameSetting.height = height;
    gameSetting.renderGroupSize = 1;
    gameSetting.maxSoundGroup = 1;
    gameSetting.levelSize = 1;
    gameSetting.layerSize = 5;

    _pCoreMgr = ::Core::CoreManager::GetInstance();

    _pCoreMgr->Initialize(gameSetting);

    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
   /* _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());
    _pCoreMgr->GetWorld()->AddActor(1, TestActor::Create());*/

    return true;
}

void Game::System::Remove()
{    
    _pCoreMgr->Release();
}

Game::System* Game::System::Create(HINSTANCE hInstance, HWND hWnd, float width, float height)
{
    System* pInstance = new System();
    if(pInstance->Initialize(hInstance, hWnd, width, height))
    {
        return pInstance;
    }
    else
    {
        pInstance->Release();
        pInstance = nullptr;
        return nullptr;
    }
}
