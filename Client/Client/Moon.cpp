#include "Moon.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/CameraActor.h"

void Client::Moon::BeginPlay()
{
	Actor::BeginPlay();

	AddComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

	pBitmapComponent->SetTextures(&_vecTextures);
	pBitmapComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));
}

void Client::Moon::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);

	Mathf::Vector2 CameraLocation = 
		_pOwnerWorld->GetCameraActor()->GetRootComponent()->GetRelativeLocation();

	Mathf::Vector2 MoonLocation = _pRootComponent->GetRelativeLocation();

	const float OriginY = 300.f;
	float CalcLocationX = CameraLocation.x + OriginY;

	_pRootComponent->SetRelativeLocation(Mathf::Vector2{CalcLocationX, MoonLocation.y});
}

void Client::Moon::Fixed()
{
}

void Client::Moon::EndPlay()
{
}
