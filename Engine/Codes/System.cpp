#include "System.h"
#include "CoreManager.h"
#include "Core_Function.h"
#include "World.h"

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

bool Game::System::Initialize(::Core::CoreManager::GameSetting gameSetting)
{
    if(!gameSetting.pWorld)
    {
		MessageBoxEx(nullptr, L"World is nullptr", L"Error", MB_OK, MB_ICONERROR);
		return false;
    }

    _pCoreMgr = ::Core::CoreManager::GetInstance();

    _pCoreMgr->Initialize(gameSetting);

	_pCoreMgr->LoadTexture(L"Client/Resources/Texture/");

    _pCoreMgr->GetWorld()->BeginPlay();

    return true;
}

void Game::System::Remove()
{    
    _pCoreMgr->Release();
}

Game::System* Game::System::Create(::Core::CoreManager::GameSetting gameSetting)
{
    System* pInstance = new System();
    if(pInstance->Initialize(gameSetting))
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
