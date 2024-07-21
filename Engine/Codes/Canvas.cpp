#include "Canvas.h"
#include "Actor.h"
#include "CoreManager.h"
#include "RenderComponent.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "CollisionComponent.h"

void Core::Canvas::Tick(_float deltaTime)
{
}

void Core::Canvas::Fixed()
{
}

void Core::Canvas::Render(ID2D1RenderTarget* pRenderTarget)
{
    pRenderTarget->SetTransform(Matx::Identity);
}

void Core::Canvas::EndPlay()
{
}

Core::Canvas* Core::Canvas::Begin()
{
	Canvas* pCanvas = new Canvas();

	return pCanvas;
}

void Core::Canvas::Remove()
{
}
