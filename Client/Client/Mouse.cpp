#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/CoreManager.h"

#include "Mouse.h"

void Client::Mouse::BeginPlay()
{
	Super::BeginPlay();

	_pBoxComponent = AddComponent<::Core::BoxComponent>("Mouse");
	_pBoxComponent->SetAddOffset({ 0.f, 0.f });
	_pBoxComponent->SetSize({ 10.f, 10.f });
	_pBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	_pBoxComponent->AddColliderInLayer();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pInputComponent->BindAction(DIM_MOVE, InputType::MOVE, this, &Mouse::OnMove);
	_pInputComponent->BindAction(DIM_LB, InputType::PRESS, this, &Mouse::OnClick);
	_pInputComponent->AttachToInputManager();
}

void Client::Mouse::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void Client::Mouse::Fixed()
{
}

void Client::Mouse::EndPlay()
{
}

void Client::Mouse::NotifyActorBlock(::Core::CollisionPackage Components)
{
}

void Client::Mouse::NotifyActorBeginOverlap(::Core::CollisionPackage Components)
{
	//if (*pOtherComponent->GetOwner() == "Timer")
	//{
	//	std::cout << "Mouse Overlap Begin" << std::endl;
	//}
}

void Client::Mouse::NotifyActorEndOverlap(::Core::CollisionPackage Components)
{
	//if (*pOtherComponent->GetOwner() == "Timer")
	//{
	//	std::cout << "Mouse Overlap End" << std::endl;
	//}
}

void Client::Mouse::OnMove(const InputEvent& inputEvent)
{
	_mousePosition = { inputEvent.x, inputEvent.y };
}

void Client::Mouse::OnClick(const InputEvent& inputEvent)
{
	if (inputEvent.key == DIM_LB && inputEvent.type == InputType::PRESS)
	{
		_pRootComponent->SetRelativeLocation({ _mousePosition.x, _mousePosition.y });
	}
	else
	{
		_pRootComponent->SetRelativeLocation({ -1.f, -1.f });
	}
}
