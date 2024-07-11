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
	_moveSpeed = 500.f;
	_gravityFactor = 50.f;
	_calculatedGravity = _gravity * _gravityFactor;
	_jumpPower = 500.f;
	_limitSpeed = 600.0f;
}

void Core::MovementComponent::TickComponent(_float deltaTime)
{
	if(!_pRootComponent)
	{
		SetRootComponent(_owner->GetRootComponent());
	}

	//Move(deltaTime);

	_velocity.y += _calculatedGravity * deltaTime;
	_velocity.y = std::min(_velocity.y, _limitSpeed);

	_pRootComponent->AddRelativeLocation(_velocity * deltaTime);
	_pRootComponent->SetVelocity(_velocity);

	if (_pRootComponent->GetWorldLocation().y > _groundPosition)
	{
		_pRootComponent->SetRelativeLocation(Mathf::Vector2(_pRootComponent->GetWorldLocation().x, _groundPosition));
		_velocity.y = 0;
		_isGrounded = true;
	}
	else
	{
		_isGrounded = false;
	}
}

void Core::MovementComponent::EndPlay()
{
}

void Core::MovementComponent::Move(float deltaTime)
{
	_velocity.x = _inputDirection.x * _moveSpeed;
}

void Core::MovementComponent::Jump(float deltaTime)
{
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
