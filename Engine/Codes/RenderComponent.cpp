#include "RenderComponent.h"
#include "Actor.h"
#include "CoreManager.h"
#include "World.h"
#include "Layer.h"
#include "Mathf.h"

bool Core::RenderComponent::Initialize()
{
	_renderMatrix = D2D1::Matrix3x2F::Scale(1.f, 1.f, D2D1::Point2F());

    return true;
}

void Core::RenderComponent::AddRenderQueueInLayer()
{
	int index = _owner->GetLayerIndex();
	CoreManager::GetInstance()->AddRenderQueue(index, this);
}

void Core::RenderComponent::RemoveRenderQueueInLayer()
{
	int index = _owner->GetLayerIndex();
	CoreManager::GetInstance()->RemoveRenderQueue(index, this);
}
