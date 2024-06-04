#include "Actor.h"
#include "Component.h"
#include "CoreManager.h"

void Core::Actor::BeginPlay()
{

}

void Core::Actor::Tick(_float deltaTime)
{
	for (auto& component : _vecComponents)
	{
		component->TickComponent(deltaTime);
	}
}

void Core::Actor::Fixed()
{

}

void Core::Actor::Render(ID2D1RenderTarget* pRenderTarget)
{

}

void Core::Actor::EndPlay()
{
}
