#include "Character.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/KhalaSystem.h"

void Client::Charactor::BeginPlay()
{
	Actor::BeginPlay();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("CrouchWalking", 0.1f, true);
	_pAnimationComponent->AddClip("Ducking", 0.1f, true);
	_pAnimationComponent->AddClip("Walk", 0.1f, true);
	//_pAnimationComponent->SetPlayClip("Walk");
	
	_pInputComponent->BindInputEvent(DIP_RT, InputType::TRIGGER, [&](const InputEvent& inputEvent)
		{
			_pInputComponent->SetVibration(0, inputEvent.value);

			/*Fire();*/
		});

	_pInputComponent->BindInputEvent(DIP_LX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			_pRootComponent->AddRelativeLocation(Mathf::Vector2{inputEvent.value, 0.f});
			_stateFlag |= MOVE;
		});

	_pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			//_pRootComponent->AddRelativeLocation(Mathf::Vector2{0.f, inputEvent.value});

			if(inputEvent.value > 0.5f)
			{
				_stateFlag |= DUCK;
			}

		});

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));

	_pInputComponent->AttachToInputManager();
}

void Client::Charactor::Tick(_float deltaTime)
{
	if (_stateFlag & MOVE && _stateFlag & DUCK)
	{
		_pAnimationComponent->SetPlayClip("CrouchWalking");
	}
	else if (_stateFlag & MOVE)
	{
		_pAnimationComponent->SetPlayClip("Walk");
	}
	else if (_stateFlag & DUCK)
	{
		_pAnimationComponent->SetPlayClip("Ducking");
	}
	else
	{
		_pAnimationComponent->SetPlayClip("Idle");
	}

	_stateFlag |= IDLE;
	_stateFlag &= ~MOVE;
	_stateFlag &= ~DUCK;

	Actor::Tick(deltaTime);

}

void Client::Charactor::Fixed()
{
}

void Client::Charactor::EndPlay()
{

}
