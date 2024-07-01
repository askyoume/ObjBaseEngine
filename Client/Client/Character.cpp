#include "Character.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/Core_Struct.h"

void Client::Charactor::BeginPlay()
{
	Actor::BeginPlay();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("CrouchWalking", 0.1f, true);
	_pAnimationComponent->AddClip("Ducking", 0.1f, true);
	_pAnimationComponent->AddClip("Walk", 0.1f, true);
	_pAnimationComponent->AddClip("Jump", 0.1f, true);
	_pAnimationComponent->AddClip("NormalAttack", 0.1f, false);
	_pAnimationComponent->AddClip("CrouchAttack", 0.1f, false);
	_pAnimationComponent->AddClip("JumpAttack", 0.1f, false);
	//_pAnimationComponent->SetPlayClip("Walk");

	_pInputComponent->BindAction(DIP_LX, InputType::AXIS, this, &Charactor::Move);
	_pInputComponent->BindAction(DIP_LY, InputType::AXIS, this, &Charactor::Duck);
	_pInputComponent->BindAction(DIP_A, InputType::PRESS, this, &Charactor::JumpHandle);
	_pInputComponent->BindAction(DIP_RIGHT_SHOULDER, InputType::PRESS, this, &Charactor::Attack);

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));

	_pInputComponent->AttachToInputManager();
}

void Client::Charactor::Tick(_float deltaTime)
{
	if(0.f != _velocity.y && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		_pAnimationComponent->SetPlayClip("JumpAttack");
	}
	else if (_stateFlag & STATE_DUCK && _stateFlag & STATE_ATTACK)
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
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _direction.x * _velocity.x * deltaTime, 0.f });
		_pAnimationComponent->SetPlayClip("CrouchWalking");
	}
	else if (_stateFlag & STATE_JUMP)
	{
		_pAnimationComponent->SetPlayClip("Jump");
	}
	else if (_stateFlag & STATE_MOVE)
	{
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _direction.x * _velocity.x * deltaTime, 0.f });
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

	_stateFlag &= ~STATE_MOVE;
	_stateFlag &= ~STATE_DUCK;

	Jump(deltaTime);

	if (_pAnimationComponent->IsClipEnd("NormalAttack") && 
		_pAnimationComponent->IsClipEnd("CrouchAttack") && 
		_pAnimationComponent->IsClipEnd("JumpAttack"))
	{
		_stateFlag &= ~STATE_ATTACK;
	}

	if (_direction.x > 0)
	{
		_pAnimationComponent->SetFlip(false);
	}
	else if (_direction.x < 0)
	{
		_pAnimationComponent->SetFlip(true);
	}

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
	if (_stateFlag & STATE_JUMP)
	{
		_stateFlag |= STATE_JUMPING;
		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ 0.f, _velocity.y * 5.f * deltaTime });
		std::cout << _velocity.y << std::endl;
		_velocity.y += _gravity.y * 5.f * deltaTime;
	}
	//temp code before made collision component
	if (_pRootComponent->GetWorldLocation().y > 220.f)
	{
		_pRootComponent->SetRelativeLocation(Mathf::Vector2(_pRootComponent->GetWorldLocation().x, 220.f));
		_velocity.y = 0.f;
			_stateFlag &= ~STATE_JUMPING;
			_stateFlag &= ~STATE_JUMP;
	}
}

void Client::Charactor::Attack(const InputEvent& inputEvent)
{
	_stateFlag |= STATE_ATTACK;
}

void Client::Charactor::Move(const InputEvent& inputEvent)
{
	_direction.x = inputEvent.value;
	_stateFlag |= STATE_MOVE;
}

void Client::Charactor::Duck(const InputEvent& inputEvent)
{
	_direction.y = inputEvent.value;
	if(DIP_LY == inputEvent.key && inputEvent.value > 0.5f)
	{
		_stateFlag |= STATE_DUCK;
	}
}

void Client::Charactor::JumpHandle(const InputEvent& inputEvent)
{
	_stateFlag |= STATE_JUMP;
	if(0.f == _velocity.y)
	_velocity.y = -200.f;
}
