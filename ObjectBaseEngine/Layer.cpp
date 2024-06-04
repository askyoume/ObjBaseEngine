#include "Layer.h"
#include "Actor.h"
#include "CoreManager.h"

void Core::Layer::Tick(_float deltaTime)
{
	for(auto& actor : _actors)
	{
		if(actor->IsDestroyMarked())
			continue;

		actor->Tick(deltaTime);
	}
}

void Core::Layer::Fixed()
{
	for(auto& actor : _actors)
	{
		if(actor->IsDestroyMarked())
			continue;

		actor->Fixed();
	}
}

void Core::Layer::Render(ID2D1RenderTarget* pRenderTarget)
{
	for(auto& actor : _actors)
	{
		if(actor->IsDestroyMarked())
			continue;

		actor->Render(pRenderTarget);
	}
}

void Core::Layer::EndPlay()
{
	CoreManager* pCoreMgr = CoreManager::GetInstance();

	for(auto& actor : _actors)
	{
		if(nullptr == actor)
			continue;

		if (!actor->IsDestroyMarked())
			continue;

		actor->EndPlay();
		pCoreMgr->AddDestroyList(actor);
		actor = nullptr;
	}
}

void Core::Layer::Remove()
{
	for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		SafeDelete(*iter);
	}

	_actors.clear();
}

Core::Layer* Core::Layer::Begin()
{
    return new Layer;
}

bool Core::Layer::AddActor(Actor* pActor)
{
    _actors.push_back(pActor);
	pActor->BeginPlay();

    return true;
}

Core::Actor* Core::Layer::GetActor(_pstring name)
{
    for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		if (!strcmp((*iter)->GetName(), name))
			return *iter;
	}

	return nullptr;
}

bool Core::Layer::DestroyActor()
{
	for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		if((*iter)->IsDestroyMarked())
		{
			SafeDelete(*iter);
			_actors.erase(iter);
			return true;
		}
	}

	return false;
}
