#include "Layer.h"
#include "Actor.h"
#include "CoreManager.h"
#include "RenderComponent.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "KhalaSystem.h"

void Core::Layer::Tick(_float deltaTime)
{
	for(auto& actor : _actors)
	{
		__Khala->ExecuteNerveCord();

		if(actor->IsDestroyMarked())
			continue;

		actor->Tick(deltaTime);
	}
		//TODO: Debug Code
	for (auto& renderComponent  : _renderQueue)
	{
		if (renderComponent->GetOwner()->IsDestroyMarked())
			continue;

		if(_pCameraActor->GetCameraComponent()->CheckCollision(renderComponent->GetCollision()))
		{
			renderComponent->SetVisible(true);
		}
		else
		{
			renderComponent->SetVisible(false);
			std::cout << "Not Visible" << std::endl;
		}
	}
}

void Core::Layer::Fixed()
{
	for(auto& actor : _actors)
	{
		__Khala->ExecuteNerveCord();

		if(actor->IsDestroyMarked())
			continue;

		actor->Fixed();
	}
}

void Core::Layer::Render(ID2D1RenderTarget* pRenderTarget)
{
	const Mathf::Matrix3x2& matrixCamera = _pCameraActor->GetCameraComponent()->GetWorldTransform();

	for (auto& renderComponent : _renderQueue)
	{
		if (renderComponent->GetOwner()->IsDestroyMarked())
			continue;

		renderComponent->SetCameraMatrix(matrixCamera);
		renderComponent->Render(pRenderTarget);
	}
}

void Core::Layer::EndPlay()
{
	CoreManager* pCoreMgr = CoreManager::GetInstance();

	if (_actors.empty())
		return;

	for (auto it = _actors.begin(); it != _actors.end();)
	{
		if (nullptr == *it)
		{
			++it;
			continue;
		}

		if (!(*it)->IsDestroyMarked())
		{
			++it;
			continue;
		}

		(*it)->EndPlay();
		pCoreMgr->AddDestroyList(*it);
		pCoreMgr->EraseActorMap(*it);
		it = _actors.erase(it); // 요소를 삭제하고 반복자를 다음 요소로 이동
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

void Core::Layer::AddRenderQueue(RenderComponent* pRenderComponent)
{
	if (nullptr == pRenderComponent)
		return;

	_renderQueue.push_back(pRenderComponent);
}

void Core::Layer::RemoveRenderQueue(RenderComponent* pRenderComponent)
{
	if (nullptr == pRenderComponent)
		return;

	_renderQueue.erase(
		std::find(_renderQueue.begin(), _renderQueue.end(), pRenderComponent));
}
