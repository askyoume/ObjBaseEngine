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
    //Ŭ���̾�Ʈ���� ���带 �����ϰ� �����ؾ���.
	//��� �����ϰ� Ŭ���̾�Ʈ���� ���带 �����ϰ� �����ϰ� �����ؾ���.
    /*_pWorld = World::Begin(); */
    // ���Ŀ� �� ���� Ŭ������ -> ���� Ŭ������ ����, ���� ���� Ŭ������ ������ ����, ��ȯ�ϴ� ��Ȱ�� ����
    
    BeginDestroy();
}

void Core::CoreManager::Tick()
{
    _pTimeMgr->UpdateTick();

    float tickTime = _pTimeMgr->GetTick();

    _pInputMgr->InputUpdate();
    if(_pWorld) { _pWorld->Tick(tickTime); }
}

void Core::CoreManager::Fixed(int count)
{
    _elapsedTick += _pTimeMgr->GetTick();

    float fixedTick = 1.f / count;

    if(_elapsedTick >= fixedTick)
	{
		if (_pWorld) { _pWorld->Fixed(); }
		_elapsedTick -= fixedTick;
	}
}

void Core::CoreManager::Render()
{
	_pRenderTarget->BeginDraw();

	_pRenderTarget->Clear();
    
    if(_pWorld) { _pWorld->Render(_pRenderTarget); }
	
	_pRenderTarget->EndDraw();

	//_pSwapChain->Present(1, 0);
}

void Core::CoreManager::EndPlay()
{
    if(_pWorld) { _pWorld->EndPlay(); }
}

void Core::CoreManager::DestroyPoint()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (true)
	{
		_variable.wait(lock, [this] { return 0 <= _toBeDestroyed.size() && _endDestroyThread; });

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
	_pWorld = info.pWorld;

    _pTimeMgr->Initialize();
    _pInputMgr->Initialize(info.hInstance, _hWnd);
    _pGraphicsMgr->Initialize(_hWnd);
	//_pSwapChain = _pGraphicsMgr->GetPackage()->_pSwapChain;
    _pRenderTarget = _pGraphicsMgr->GetPackage()->_pHwndRenderTarget;

    _pTextureMgr->Initialize(_pGraphicsMgr->GetPackage());

	//if (!_pWorld)
 //   {
	//	_pWorld = World::Begin();
 //   }

    _pWorld->InitializeWorld(info.layerSize);
}

HWND Core::CoreManager::GetWindowHandle() const
{
    return _hWnd;
}

void Core::CoreManager::AddDestroyList(Object* pObject)
{
    if (pObject == nullptr) return;  // ��ȿ���� ���� ������ ����

    std::lock_guard<std::mutex> lock(_mutex);
    _toBeDestroyed.push_back(pObject);
    
    // ������ �����ϸ� �����忡 ��ȣ ����
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
    _endDestroyThread = true;
    _variable.notify_one();
	_destructionThread.join();
}

bool Core::CoreManager::LoadTexture(_pwstring filePath)
{
	return _pTextureMgr->LoadTexture(filePath);
}

Core::Texture* Core::CoreManager::FindTexture(_pwstring filePath)
{
	return _pTextureMgr->FindTexture(filePath);
}

GraphicsPtrPackage* Core::CoreManager::GetGraphicsPackage() const
{
	return _pGraphicsMgr->GetPackage();
}

void Core::CoreManager::Remove()
{
	//_pSwapChain = nullptr;
	_pRenderTarget = nullptr;

    EndDestroy();

	SafeDelete(_pWorld);
    SafeDelete(_pTimeMgr);
	SafeDelete(_pInputMgr);
	SafeDelete(_pTextureMgr);
	SafeDelete(_pGraphicsMgr);

	_endPlay = true;
}