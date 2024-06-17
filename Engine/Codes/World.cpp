#include "World.h"
#include "Actor.h"
#include "Layer.h"
#include "SceneComponent.h"

bool Core::World::InitializeWorld(int layerSize)
{
    InitializeLayer(layerSize);

	return true;
}

void Core::World::Remove()
{
	ClearLayer();
}

void Core::World::Tick(_float deltaTime)
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Tick(deltaTime);
	}
}

void Core::World::Fixed()
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Fixed();
	}
}

void Core::World::Render(ID2D1RenderTarget* pRenderTarget)
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Render(pRenderTarget);
	}
}

void Core::World::EndPlay()
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->EndPlay();
	}

}

bool Core::World::InitializeLayer(int layerSize)
{
    _layerSize = layerSize;
	for (int i = 0; i < layerSize; i++)
	{
		Layer* pLayer = Layer::Begin();
		_vecLayers.push_back(pLayer);
	}

	return true;
}

Core::Layer* Core::World::GetLayer(int layerIndex) const
{
	if (layerIndex < _vecLayers.size())
	{
		return _vecLayers[layerIndex];
	}

	return nullptr;
}

void Core::World::AddLayer(int layerIndex, Layer* pLayer)
{
	_vecLayers.push_back(pLayer);
}

void Core::World::RemoveLayer(int layerIndex)
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		if (*iter == _vecLayers[layerIndex])
		{
			SafeDelete(*iter);
			_vecLayers.erase(iter);
			break;
		}
	}
}

void Core::World::ClearLayer()
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Release();
	}

	_vecLayers.clear();
}

bool Core::World::SpawnActor(int layerIndex, _pstring name, Actor* pActor)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);

	_actorMap.insert(std::make_pair(name, pActor));
	_vecLayers[layerIndex]->AddActor(pActor);

	return true;
}

bool Core::World::SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);

	pActor->GetRootComponent()->SetRelativeLocation(location);

	_actorMap.insert(std::make_pair(name, pActor));
	_vecLayers[layerIndex]->AddActor(pActor);

	return true;
}

bool Core::World::RemoveActor(_pstring name)
{
	_actorMap.find(name)->second->OnDestroyMark(true);

	return true;
}

Core::Actor* Core::World::FindActor(_pstring name)
{
    return _actorMap.find(name)->second;
}
