#include "Aoko.h"
#include "AokoFSMContainer.h"
#include "../../Engine/Headers/Core_Struct.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/StateComponent.h"

void Client::Aoko::BeginPlay()
{
	Actor::BeginPlay();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("ReadyToRuning", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToIdle", 0.1f, false);
	_pAnimationComponent->AddClip("Runing", 0.1f, true);
	_pAnimationComponent->AddClip("LowKick", 0.1f, false);

	_pInputComponent->BindAction(DIP_LX, InputType::AXIS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::PRESS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_LEFT, InputType::PRESS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::RELEASE, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_LEFT, InputType::RELEASE, this, &Aoko::Move);

	_pInputComponent->AttachToInputManager();

	_pStateComponent = AddComponent<::Core::StateComponent>("StateComponent");
	_pStateComponent->AddContainer<AokoFSMContainer>();

	SetPlayClip("Idle");
}

void Client::Aoko::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);
}

void Client::Aoko::Fixed()
{
}

void Client::Aoko::EndPlay()
{
}

void Client::Aoko::Attack(const InputEvent& inputEvent)
{
}

void Client::Aoko::Move(const InputEvent& inputEvent)
{
	//_direction.x = inputEvent.value;
	//_direction.y = inputEvent.value;
	if (inputEvent.key == DIK_LEFT && inputEvent.type == InputType::PRESS)
	{
		_direction.x = -1;
	}
	else if (inputEvent.key == DIK_RIGHT && inputEvent.type == InputType::PRESS)
	{
		_direction.x = 1;
	}
	else if (inputEvent.type == InputType::RELEASE)
	{
		_direction.x = 0;
	}
}

void Client::Aoko::Dead()
{
}

void Client::Aoko::SetPlayClip(_pstring clipName)
{
	_pAnimationComponent->SetPlayClip(clipName);
}
