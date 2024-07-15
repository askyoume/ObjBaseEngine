#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"

#include "Neko.h"
#include "AIMovementFSMContainer.h"

void Client::Neko::BeginPlay()
{
	Super::BeginPlay();
	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");
	_pMovementComponent = AddComponent<::Core::MovementComponent>("MovementComponent");
	_pMovementComponent->SetGroundPosition(80.f);

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("Move", 0.1f, true);
	_pAnimationComponent->AddClip("BackMove", 0.1f, true);
	//_pAnimationComponent->AddClip("Jump", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToBackMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToRuning", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToIdle", 0.1f, false);
	_pAnimationComponent->AddClip("Runing", 0.1f, true);
	_pAnimationComponent->AddClip("LowKick", 0.1f, false);

	_pBoxComponent = AddComponent<::Core::BoxComponent>("BoxComponent");
	_pBoxComponent->SetSize({ 90.f, 550.f });
	_pBoxComponent->AddColliderInLayer();
	_pBoxComponent->AddRenderQueueInLayer();

	_pAIComponent = AddComponent<::Core::StateComponent>("AIComponent");
	_pAIComponent->AddContainer<AIMovementFSMContainer>();

	_pAnimationComponent->SetPlayClip("Idle");
}

void Client::Neko::Tick(_float deltaTime)
{
	Super::Tick(deltaTime);
}

void Client::Neko::Fixed()
{
}

void Client::Neko::EndPlay()
{
}

Client::Neko* Client::Neko::Create()
{
	return new Neko;
}