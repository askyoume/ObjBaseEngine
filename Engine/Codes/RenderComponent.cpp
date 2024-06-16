#include "RenderComponent.h"
#include "Actor.h"
#include "CoreManager.h"
#include "World.h"
#include "Layer.h"
#include "Mathf.h"

bool Core::RenderComponent::Initialize()
{
	//���� ��� ��ȯ -> Viewport ��ǥ���� �߽��� �������� Y���� �ڱ� ���� ���(��Ʈ���� ���� ����)
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