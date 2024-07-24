#include "NightSky.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"

void Client::NightSky::BeginPlay()
{
	Actor::BeginPlay();

	AddComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

	pBitmapComponent->SetTextures(&_vecTextures);
	pBitmapComponent->SetRelativeScale(Mathf::Vector2(12.f, 12.f));
}

void Client::NightSky::Tick(_float deltaSeconds)
{
	Actor::Tick(deltaSeconds);
}

void Client::NightSky::Fixed()
{
}

void Client::NightSky::EndPlay()
{
}
