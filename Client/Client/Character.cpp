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
	_pAnimationComponent->AddClip("NormalAttack", 0.1f, false);
	_pAnimationComponent->AddClip("CrouchAttack", 0.1f, false);
	//_pAnimationComponent->SetPlayClip("Walk");
	
	_pInputComponent->BindInputEvent(DIP_RIGHT_SHOULDER, InputType::PRESS, [&](const InputEvent& inputEvent)
		{
			if (DIP_RIGHT_SHOULDER == inputEvent.key)
			{
				_stateFlag |= STATE_ATTACK;
			}
		});

	_pInputComponent->BindInputEvent(DIP_LX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			_directionX = inputEvent.value;
			_stateFlag |= STATE_MOVE;
		});

	_pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			_directionY = inputEvent.value;
			if(DIP_LY == inputEvent.key && inputEvent.value > 0.5f)
			{
				_stateFlag |= STATE_DUCK;
			}
		});

	_pInputComponent->BindInputEvent(DIP_A, InputType::PRESS, [&](const InputEvent& inputEvent)
		{
				_stateFlag |= STATE_JUMP;
		});

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));

	_pInputComponent->AttachToInputManager();
}

void Client::Charactor::Tick(_float deltaTime)
{
	if (_stateFlag & STATE_DUCK && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		_pAnimationComponent->SetPlayClip("CrouchAttack");
	}
	else if (_stateFlag & STATE_MOVE && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		_pAnimationComponent->SetPlayClip("NormalAttack");
	}
	else if (_stateFlag & STATE_MOVE && _stateFlag & STATE_DUCK)
	{
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _directionX * 160.f * deltaTime, 0.f });
		_pAnimationComponent->SetPlayClip("CrouchWalking");
	}
	else if (_stateFlag & STATE_MOVE)
	{
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _directionX * 160.f * deltaTime, 0.f });
		_pAnimationComponent->SetPlayClip("Walk");
	}
	else if (_stateFlag & STATE_DUCK)
	{
		_pAnimationComponent->SetPlayClip("Ducking");
	}
	else if (_stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		_pAnimationComponent->SetPlayClip("NormalAttack");
	}
	else
	{
		_pAnimationComponent->SetPlayClip("Idle");
		_stateFlag |= STATE_IDLE;
	}

	if (_stateFlag & STATE_JUMP && !(_stateFlag & STATE_JUMPING))
	{
		Jump(deltaTime);
	}
	else if(220.f > _pRootComponent->GetRelativeLocation().y)
	{
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ 0.f, _jumpPower * deltaTime });
	}
	else if (220.f <= _pRootComponent->GetRelativeLocation().y)
	{
		_stateFlag &= ~STATE_JUMPING;
	}

	_stateFlag &= ~STATE_MOVE;
	_stateFlag &= ~STATE_DUCK;
	_stateFlag &= ~STATE_ATTACK;
	_stateFlag &= ~STATE_JUMP;

	std::cout << _directionX << " " << _directionY << std::endl;

	Actor::Tick(deltaTime);

}

void Client::Charactor::Fixed()
{

}

void Client::Charactor::EndPlay()
{

}

void Client::Charactor::Jump(_float deltaTime)
{
	_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _directionX * _jumpPower * deltaTime, -_jumpPower * deltaTime });
}
