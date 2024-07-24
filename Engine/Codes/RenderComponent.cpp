#include "RenderComponent.h"
#include "Actor.h"
#include "CoreManager.h"
#include "World.h"
#include "Layer.h"
#include "Mathf.h"

bool Core::RenderComponent::Initialize()
{
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

void Core::RenderComponent::SetCameraMatrix(const Mathf::Matrix3x2& cameraMatrix)
{
	_cameraMatrix = cameraMatrix;
	D2D1InvertMatrix(&_cameraMatrix);
}
