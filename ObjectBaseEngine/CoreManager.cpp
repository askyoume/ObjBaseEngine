#include "CoreManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "Object.h"
#include "World.h"

Core::CoreManager::CoreManager()
{
    _pTimeMgr = TimeManager::Create();
    _pInputMgr = InputManager::Create();
    _pGraphicsMgr = GraphicsManager::Create();
    _pTextureMgr = TextureManager::Create();
    _pWorld = World::Begin(); // 추후에 현 월드 클래스를 -> 레벨 클래스로 변경, 이후 월드 클래스는 레벨을 관리, 전환하는 역활을 수행
    BeginDestroy();
}

void Core::CoreManager::Tick()
{
    _pTimeMgr->UpdateTick();
    std::cout << _toBeDestroyed.size() << std::endl;

    float tickTime = _pTimeMgr->GetTick();

    _pInputMgr->InputUpdate();
	_pWorld->Tick(tickTime);
}

void Core::CoreManager::Fixed(int count)
{
    _elapsedTick += _pTimeMgr->GetTick();

    float fixedTick = 1.f / count;

    if(_elapsedTick >= fixedTick)
	{
		_pWorld->Fixed();
		_elapsedTick -= fixedTick;
	}
}

void Core::CoreManager::Render()
{
	_pRenderTarget->BeginDraw();

	_pRenderTarget->Clear();
    
	_pWorld->Render(_pRenderTarget);
	
	_pRenderTarget->EndDraw();

	//_pSwapChain->Present(1, 0);
}

void Core::CoreManager::EndPlay()
{
    _pWorld->EndPlay();
}

void Core::CoreManager::DestroyPoint()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (true)
	{
		_variable.wait(lock, [this] { return !_toBeDestroyed.empty() || _endDestroyThread; });

		if (_endDestroyThread && _toBeDestroyed.empty()) break;

		for (auto& pObject : _toBeDestroyed)
		{
			SafeDelete(pObject);
		}

		_toBeDestroyed.clear();
	}
}

void Core::CoreManager::Initialize(const GameSetting& info)
{
    _hWnd = info.hWnd;
	_width = info.width;
	_height = info.height;

    _pTimeMgr->Initialize();
    _pInputMgr->Initialize(info.hInstance, _hWnd);
    _pGraphicsMgr->Initialize(_hWnd);
	//_pSwapChain = _pGraphicsMgr->GetPackage()->_pSwapChain;
    _pRenderTarget = _pGraphicsMgr->GetPackage()->_pHwndRenderTarget;

    _pTextureMgr->Initialize(_pGraphicsMgr->GetPackage());
    _pWorld->InitializeWorld(info.layerSize);
}

HWND Core::CoreManager::GetWindowHandle() const
{
    return _hWnd;
}

void Core::CoreManager::AddDestroyList(Object* pObject)
{
    if (pObject == nullptr) return;  // 유효하지 않은 포인터 검증

    std::lock_guard<std::mutex> lock(_mutex);
    _toBeDestroyed.push_back(pObject);
    
    // 조건을 충족하면 스레드에 신호 보냄
    if (_toBeDestroyed.size() >= 20)
    {
        _variable.notify_one();
    }
}

void Core::CoreManager::BeginDestroy()
{
    _destructionThread = std::thread(&CoreManager::DestroyPoint, this);
}

void Core::CoreManager::EndDestroy()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _endDestroyThread = true;

    _variable.notify_one();
    _destructionThread.join();
}

void Core::CoreManager::Remove()
{
	//_pSwapChain = nullptr;
	_pRenderTarget = nullptr;
    EndDestroy();

	SafeDelete(_pWorld);
    SafeDelete(_pTimeMgr);
	SafeDelete(_pInputMgr);
	SafeDelete(_pGraphicsMgr);
	SafeDelete(_pTextureMgr);

	_endPlay = true;
}
