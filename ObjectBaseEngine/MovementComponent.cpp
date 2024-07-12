#include "MovementComponent.h"
#include "SceneComponent.h"
#include "Transform.h"
#include "Actor.h"

#undef min
#undef max

bool Core::MovementComponent::Initialize()
{
	BeginPlay();

	return true;
}

void Core::MovementComponent::BeginPlay()
{
	//default settings
	_moveSpeed = 150.f;
	_gravityFactor = 450.f;
	_calculatedGravity = _gravity * _gravityFactor;
	_jumpPower = 1500.f;
	_limitSpeed = 100.0f;

	_acceleration = 4.f;
	_friction = 0.98f;
	_targetSpeed = 0.f;
}

void Core::MovementComponent::TickComponent(_float deltaTime)
{
	if(!_pRootComponent)
	{
		SetRootComponent(_owner->GetRootComponent());
	}

	_ownerCurrentLocation = _pRootComponent->GetWorldLocation();

	_velocity.y += _calculatedGravity * deltaTime;

	if (_velocity.x > 0)
	{
		_velocity.x = std::max(_velocity.x, -_limitSpeed);
	}
	else
	{
		_velocity.x = std::min(_velocity.x, _limitSpeed);
	}

	_pRootComponent->AddRelativeLocation(_velocity * deltaTime);
	_pRootComponent->SetVelocity(_velocity);

	_velocity.x *= _friction;

	if (_ownerCurrentLocation.y > _groundPosition)
	{
		_pRootComponent->SetRelativeY(_groundPosition);
		_velocity.y = 0.f;
		_isGrounded = true;
	}

	_isJumping = false;
}

void Core::MovementComponent::EndPlay()
{
}

void Core::MovementComponent::Move(float deltaTime)
{
	_velocity.x = _inputDirection.x * _moveSpeed;
}

void Core::MovementComponent::Run(float deltaTime)
{
	if(_isRunning)
		_velocity.x = _inputDirection.x * _acceleration * _moveSpeed;
}

void Core::MovementComponent::Jump(float deltaTime)
{
	if (_isGrounded && !_isJumping)
	{
		_velocity.y = _inputDirection.y * _jumpPower;
		_isGrounded = false;
		_isJumping = true;
	}
}

Core::MovementComponent* Core::MovementComponent::Create()
{
	MovementComponent* pInstance = new MovementComponent;
	if (pInstance->Initialize())
	{
		return pInstance;
	}

	return nullptr;
}
