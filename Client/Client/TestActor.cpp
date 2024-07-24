#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"

#include "TestActor.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("BitmapComponent");
	_pBitmapComponent->SetTextures(&_vecTextures);
}

void Client::TestActor::Tick(_float deltaSeconds)
{
	Actor::Tick(deltaSeconds);
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::EndPlay()
{
}
