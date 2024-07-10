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
	_pAnimationComponent->AddClip("Runing", 0.1f, true);

	_pInputComponent->BindAction(DIP_LX, InputType::AXIS, this, &Aoko::Move);
	_pInputComponent->AttachToInputManager();

	_pStateComponent = AddComponent<::Core::StateComponent>("StateComponent");
	_pStateComponent->AddContainer<AokoFSMContainer>();
}

void Client::Aoko::Tick(_float deltaTime)
{
	//if (0.5f < _direction.x || -0.5 > _direction.x)
	//{
	//	_pAnimationComponent->SetPlayClip("Runing");
	//	if (_direction.x > 0.f)
	//		_pAnimationComponent->SetFlip(false);
	//	else
	//		_pAnimationComponent->SetFlip(true);
	//	Mathf::Vector2 _velocity{ 1.f, 0.f };
	//	Mathf::Vector2 _position = _pRootComponent->GetRelativeLocation();

	//	_pRootComponent->SetRelativeLocation(_position + _velocity * _direction.x);
	//	std::cout << _direction.x << std::endl;
	//}
	//else
	//{
	//	_pAnimationComponent->SetPlayClip("Idle");
	//}


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
	_direction.x = inputEvent.value;
	_direction.y = inputEvent.value;
}

void Client::Aoko::Dead()
{
}

void Client::Aoko::SetPlayClip(_pstring clipName)
{
	_pAnimationComponent->SetPlayClip(clipName);
}
