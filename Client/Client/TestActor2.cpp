#include "TestActor2.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"

void Client::TestActor2::BeginPlay()
{
	Actor::BeginPlay();

	AddComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

		pBitmapComponent->SetTextures(&_vecTextures);
		pBitmapComponent->AddRenderQueueInLayer();
}

void Client::TestActor2::Tick(_float deltaTime)
{
		Actor::Tick(deltaTime);
}

void Client::TestActor2::Fixed()
{
}

void Client::TestActor2::EndPlay()
{
}

void Client::TestActor2::Remove()
{
	for (auto& component : _vecComponents)
		SafeDelete(component);

	_vecComponents.clear();
}
