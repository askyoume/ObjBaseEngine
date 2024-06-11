#include "RenderComponent.h"
#include "Mathf.h"

bool Core::RenderComponent::Initialize()
{
	_renderMatrix = D2D1::Matrix3x2F::Scale(1.f, -1.f, D2D1::Point2F(0,0));

    return true;
}
