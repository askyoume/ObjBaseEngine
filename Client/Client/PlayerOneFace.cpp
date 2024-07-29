#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"

#include "PlayerOneFace.h"

void Client::PlayerOneFace::BeginPlay()
{
	Super::BeginPlay();

	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("InnerPlate");
	_pBitmapComponent->SetTextures(&_vecTextures);
	_pBitmapComponent->SetOrder(2);

	_pBitmapComponent2 = AddComponent<::Core::BitmapComponent>("OuterFace");
	_pBitmapComponent2->SetTextures(&_vecTextures);
	_pBitmapComponent2->SetBitmapIndex(1);
	_pBitmapComponent2->SetRelativeLocation({ 0.f, -5.f });
	_pBitmapComponent2->SetOrder(1);

	_pBitmapComponent3 = AddComponent<::Core::BitmapComponent>("namePlate");
	_pBitmapComponent3->SetTextures(&_vecTextures);
	_pBitmapComponent3->SetBitmapIndex(2);
	_pBitmapComponent3->SetRelativeLocation({ 145.f, 85.f });
	_pBitmapComponent3->SetOrder(1);

	_pBitmapComponent4 = AddComponent<::Core::BitmapComponent>("BottomPlate");
	_pBitmapComponent4->SetTextures(&_vecTextures);
	_pBitmapComponent4->SetBitmapIndex(3);
	_pBitmapComponent4->SetRelativeLocation({ 0.f, 90.f });
	_pBitmapComponent4->SetOrder(2);

	_pRootComponent->SetRelativeScale({ 1.5f, 1.5f });
}

void Client::PlayerOneFace::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void Client::PlayerOneFace::Fixed()
{
}

void Client::PlayerOneFace::EndPlay()
{
}
