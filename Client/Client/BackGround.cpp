#include "BackGround.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/CameraActor.h"

void Client::BackGround::BeginPlay()
{
	Actor::BeginPlay();

	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");

	_pAnimationComponent->AddClip("Idle", 0.2f, true);

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(3.f, 1.5f));

	_pAnimationComponent->SetPlayClip("Idle");

	//AddComponent<::Core::BitmapComponent>("BitmapComponent");

	//::Core::BitmapComponent* pBitmapComponent =
	//	GetComponent<::Core::BitmapComponent>("BitmapComponent");

	//pBitmapComponent->SetTextures(&_vecTextures);
	//pBitmapComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));
}

void Client::BackGround::Tick(_float deltaSeconds)
{
	Actor::Tick(deltaSeconds);

	//float BackgroundLocationY = -180.f;
 //   float BackgroundStartX = 125.0f;
 //   float BackgroundEndX = 492.0f;
 //   float maxCameraX = 650.f;

	//Mathf::Vector2 CameraLocation = 
	//	_pOwnerWorld->GetCameraActor()->GetRootComponent()->GetRelativeLocation();

 //   float CalcLocationX = (CameraLocation.x / maxCameraX) * 
	//	(BackgroundEndX - BackgroundStartX) + BackgroundStartX;
 //   
	//_pRootComponent->SetRelativeLocation(Mathf::Vector2{CalcLocationX, BackgroundLocationY});

}

void Client::BackGround::Fixed()
{
}

void Client::BackGround::EndPlay()
{
}
