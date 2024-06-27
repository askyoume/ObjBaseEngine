#include "CoreManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Object.h"
#include "World.h"
#include "Layer.h"
#include "Mathf.h"

Core::CoreManager::CoreManager()
{
    _pTimeMgr = TimeManager::Create();
    _pInputMgr = InputManager::Create();
    _pGraphicsMgr = GraphicsManager::Create();
    _pTextureMgr = TextureManager::Create();
	_pFontMgr = FontManager::Create();
    //Ŭ���̾�Ʈ���� ���带 �����ϰ� ����(?)�� �����ؾ���.
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
	bool isZero = count == 0;
	if (isZero) return;

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

    _pWorld->InitializeWorld(info.layerSize);
}

HWND Core::CoreManager::GetWindowHandle() const
{
    return _hWnd;
}

void Core::CoreManager::AddDestroyList(Object* pObject)
{
    if (pObject == nullptr) return;  // ��ȿ���� ���� ������ ����

	if(20 >= _toBeDestroyed.size())
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_toBeDestroyed.push_back(pObject);
	}
    
    // ������ �����ϸ� �����忡 ��ȣ ����
    if (20 == _toBeDestroyed.size())
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

void Core::CoreManager::RegisterAction(_pstring actionName, InputComponent* component)
{
	_pInputMgr->RegisterAction(actionName, component);
}

void Core::CoreManager::UnRegisterAction(_pstring actionName, InputComponent* component)
{
	_pInputMgr->UnRegisterAction(actionName, component);
}

void Core::CoreManager::RegisterKey(InputDevice device, _uint key, InputType type, InputComponent* component)
{
	_pInputMgr->RegisterKey(device, key, type, component);
}

void Core::CoreManager::UnRegisterKey(InputDevice device, _uint key, InputType type, InputComponent* component)
{
	_pInputMgr->UnRegisterKey(device, key, type, component);
}

void Core::CoreManager::EraseActorMap(Object* pObject)
{
    _pWorld->GetActorMap().erase(pObject->GetName());
}

Core::Layer* Core::CoreManager::GetLayer(int layerIndex) const
{
	if (_pWorld)
    {
		return _pWorld->GetLayer(layerIndex);
    }

    return nullptr;
}

void Core::CoreManager::AddRenderQueue(int layerIndex, RenderComponent* pRenderComponent)
{
	if (_pWorld)
	{
		_pWorld->GetLayer(layerIndex)->AddRenderQueue(pRenderComponent);
	}
}

void Core::CoreManager::RemoveRenderQueue(int layerIndex, RenderComponent* pRenderComponent)
{
	if (_pWorld)
	{
		_pWorld->GetLayer(layerIndex)->RemoveRenderQueue(pRenderComponent);
	}
}

GraphicsPtrPackage* Core::CoreManager::GetGraphicsPackage() const
{
	return _pGraphicsMgr->GetPackage();
}

_pFont Core::CoreManager::LoadFont(_pwstring fontName, _pwstring fontPath, float fontSize)
{
	_pFontMgr->LoadFontFile(fontPath, fontName, fontSize);

	return _pFontMgr->GetFont(fontName);
}

_pFont Core::CoreManager::GetFont(_pwstring fontName)
{
	return _pFontMgr->GetFont(fontName);
}

void Core::CoreManager::Remove()
{
	//_pSwapChain = nullptr;
	_pRenderTarget = nullptr;

    EndDestroy();

	SafeDelete(_pWorld);
	SafeDelete(_pFontMgr);
    SafeDelete(_pTimeMgr);
	SafeDelete(_pInputMgr);
	SafeDelete(_pTextureMgr);
	SafeDelete(_pGraphicsMgr);

	_endPlay = true;
}
