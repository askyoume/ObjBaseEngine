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

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(3.f, 2.f));

	_pAnimationComponent->SetPlayClip("Idle");
}

void Client::BackGround::Tick(_float deltaSeconds)
{
	Actor::Tick(deltaSeconds);
}

void Client::BackGround::Fixed()
{
}

void Client::BackGround::EndPlay()
{
}
