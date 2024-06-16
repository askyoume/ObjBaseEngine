#include "RenderComponent.h"
#include "Actor.h"
#include "CoreManager.h"
#include "World.h"
#include "Layer.h"
#include "Mathf.h"

bool Core::RenderComponent::Initialize()
{
	//렌더 행렬 변환 -> Viewport 좌표계의 중심을 기준으로 Y축을 뒤기 위한 행렬(비트맵의 상하 반전)
	_renderMatrix = D2D1::Matrix3x2F::Scale(1.f, -1.f, D2D1::Point2F(
		0.f,
		CoreManager::GetInstance()->GetHeight() / 2.f
	));

    return true;
}

void Core::RenderComponent::AddRenderQueueInLayer()
{
	int index = _owner->GetLayerIndex();
	CoreManager::GetInstance()->AddRenderQueue(index, this);
}