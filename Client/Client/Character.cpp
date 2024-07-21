#include "Character.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/Core_Struct.h"

void Client::Character::BeginPlay()
{
	Actor::BeginPlay();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent1");
	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("CrouchWalking", 0.1f, true);
	_pAnimationComponent->AddClip("Ducking", 0.1f, true);
	_pAnimationComponent->AddClip("Walk", 0.1f, true);
	_pAnimationComponent->AddClip("Jump", 0.1f, true);
	_pAnimationComponent->AddClip("NormalAttack", 0.1f, false);
	_pAnimationComponent->AddClip("NormalDirAttack", 0.1f, false);
	_pAnimationComponent->AddClip("NormalUpAttack", 0.1f, false);
	_pAnimationComponent->AddClip("CrouchAttack", 0.1f, false);
	_pAnimationComponent->AddClip("JumpAttack", 0.1f, false);
	_pAnimationComponent->AddClip("JumpDirAttack", 0.1f, false);
	_pAnimationComponent->AddClip("JumpDownAttack", 0.1f, false);

	_pInputComponent->BindAction(DIP_LX, InputType::AXIS, this, &Character::Move);
	_pInputComponent->BindAction(DIP_LY, InputType::AXIS, this, &Character::Duck);
	_pInputComponent->BindAction(DIP_A, InputType::PRESS, this, &Character::JumpHandle);
	_pInputComponent->BindAction(DIP_RIGHT_SHOULDER, InputType::PRESS, this, &Character::Attack);
	_pInputComponent->BindAction(DIK_AXIS, InputType::AXIS, this, &Character::Move);

	_pAnimationComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));

	_pInputComponent->AttachToInputManager();
}

void Client::Character::Tick(_float deltaTime)
{
	if(0.f != _velocity.y && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);

		if(_stateFlag & STATE_DIR_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("JumpDirAttack");
			std::cout << "attack" << std::endl;
		}
		else if (_stateFlag & STATE_UP_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("JumpDownAttack");
		}
		else
		{
			_pAnimationComponent->SetPlayClip("JumpAttack");
		}
	}
	else if (_stateFlag & STATE_DUCK && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		_pAnimationComponent->SetPlayClip("CrouchAttack");
	}
	else if (_stateFlag & STATE_MOVE && _stateFlag & STATE_ATTACK)
	{
		_pInputComponent->SetVibration(0.f, 255.f);
		if(_stateFlag & STATE_DIR_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("NormalDirAttack");
		}
		else if (_stateFlag & STATE_UP_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("NormalUpAttack");
		}
		else
		{
			_pAnimationComponent->SetPlayClip("NormalAttack");
		}
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
		if(_stateFlag & STATE_DIR_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("NormalDirAttack");
		}
		else if (_stateFlag & STATE_UP_ATTACK)
		{
			_pAnimationComponent->SetPlayClip("NormalUpAttack");
		}
		else
		{
			_pAnimationComponent->SetPlayClip("NormalAttack");
		}
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
		_pAnimationComponent->IsClipEnd("JumpAttack") &&
		_pAnimationComponent->IsClipEnd("NormalDirAttack") &&
		_pAnimationComponent->IsClipEnd("NormalUpAttack") &&
		_pAnimationComponent->IsClipEnd("JumpDirAttack") &&
		_pAnimationComponent->IsClipEnd("JumpDownAttack"))
	{
		_stateFlag &= ~STATE_ATTACK;
		_stateFlag &= ~STATE_DIR_ATTACK;
		_stateFlag &= ~STATE_UP_ATTACK;
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

void Client::Character::Fixed()
{

}

void Client::Character::EndPlay()
{

}

void Client::Character::Jump(_float deltaTime)
{
	if (_stateFlag & STATE_JUMP)
	{
		_stateFlag |= STATE_JUMPING;

		_velocity.x = _direction.x * 90.f;

		_pRootComponent->AddRelativeLocation(Mathf::Vector2{ _velocity.x * 5.f * deltaTime, _velocity.y * 5.f * deltaTime });
		//std::cout << _velocity.y << std::endl;
		_velocity.y += _gravity.y * 5.f * deltaTime;
		_velocity.x += _velocity.x * 5.f * deltaTime;

	}
	//temp code before made collision component
	if (_pRootComponent->GetWorldLocation().y > 150.f)
	{
		_pRootComponent->SetRelativeLocation(Mathf::Vector2(_pRootComponent->GetWorldLocation().x, 150.f));
		_velocity.x = 200.f;
		_velocity.y = 0.f;
			_stateFlag &= ~STATE_JUMPING;
			_stateFlag &= ~STATE_JUMP;
	}
}

void Client::Character::Attack(const InputEvent& inputEvent)
{
	_stateFlag |= STATE_ATTACK;

	if(_stateFlag & STATE_DIR_ATTACK && _stateFlag & STATE_UP_ATTACK)
		return;

	if (0.f != _velocity.y && _direction.y > 0.6f && _direction.y < 0.98f)
	{
		_stateFlag |= STATE_DIR_ATTACK;

	}
	else if (0.f != _velocity.y && _direction.y > 0.95f)
	{
		_stateFlag |= STATE_UP_ATTACK;
	}
	else if(_direction.y < -0.6f && _direction.y > -0.95f)
	{
		_stateFlag |= STATE_DIR_ATTACK;
	}
	else if (_direction.y < -0.95f)
	{
		_stateFlag |= STATE_UP_ATTACK;
	}
}

void Client::Character::Move(const InputEvent& inputEvent)
{
	_direction.x = inputEvent.value;
	_stateFlag |= STATE_MOVE;
}

void Client::Character::Duck(const InputEvent& inputEvent)
{
	_direction.y = inputEvent.value;
	if(DIP_LY == inputEvent.key && inputEvent.value > 0.5f)
	{
		_stateFlag |= STATE_DUCK;
	}
}

void Client::Character::JumpHandle(const InputEvent& inputEvent)
{
	_stateFlag |= STATE_JUMP;
	if(0.f == _velocity.y)
	_velocity.y = -200.f;
}
