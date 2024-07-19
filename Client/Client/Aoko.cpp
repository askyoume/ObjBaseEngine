#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"

#include "Aoko.h"
#include "ClientFSMContainer.h"

void Client::Aoko::BeginPlay()
{
	Super::BeginPlay();

	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");
	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pMovementComponent = AddComponent<::Core::MovementComponent>("MovementComponent");
	_pMovementComponent->SetGroundPosition(80.f);

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("Move", 0.1f, true);
	_pAnimationComponent->AddClip("BackMove", 0.1f, true);
	_pAnimationComponent->AddClip("Jump", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToBackMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToRunning", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToIdle", 0.1f, false);
	_pAnimationComponent->AddClip("Running", 0.1f, true);
	_pAnimationComponent->AddClip("LowKick", 0.06f, false);
	_pAnimationComponent->AddClip("MiddleKick", 0.06f, false);
	_pAnimationComponent->SetPlayClip("Idle");

	//rip... need to change this(단순한게 쓰기도 좋다... 이건 너무 복잡, 구현도 그렇고, 이해도 그렇고)
	//move to input component
	_pInputComponent->BindAction(DIK_RIGHT, InputType::PRESS, this, &Aoko::RightMoveHandler);
	_pInputComponent->BindAction(DIK_LEFT, InputType::PRESS, this, &Aoko::LeftMoveHandler);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::HELD, this, &Aoko::RightMoveHandler);
	_pInputComponent->BindAction(DIK_LEFT, InputType::HELD, this, &Aoko::LeftMoveHandler);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::RELEASE, this, &Aoko::StandHandler);
	_pInputComponent->BindAction(DIK_LEFT, InputType::RELEASE, this, &Aoko::StandHandler);
	//jump to input component
	_pInputComponent->BindAction(DIK_UP, InputType::PRESS, this, &Aoko::Jump);
	//attack to input component
	_pInputComponent->BindAction(DIK_S, InputType::PRESS, this, &Aoko::LowKickHandler);
	_pInputComponent->BindAction(DIK_D, InputType::PRESS, this, &Aoko::MiddleKickHandler);
	//input component attach to input manager
	_pInputComponent->AttachToInputManager();

	_pStateComponent = AddComponent<::Core::StateComponent>("StateComponent");
	_pStateComponent->AddContainer<ClientFSMContainer>();

	_pBodyBoxComponent = AddComponent<::Core::BoxComponent>("BodyBoxComponent");
	_pBodyBoxComponent->SetAddOffset({ 0.f, 100.f });
	_pBodyBoxComponent->SetSize({ 100.f, 400.f });
	_pBodyBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	_pBodyBoxComponent->AddColliderInLayer();

	_pFootBoxComponent = AddComponent<::Core::BoxComponent>("FootBoxComponent");
	_pFootBoxComponent->SetAddOffset({ 200.f, 100.f });
	_pFootBoxComponent->SetSize({ 270.f, 100.f });
	_pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	_pFootBoxComponent->AddColliderInLayer();
}

void Client::Aoko::Tick(_float deltaTime)
{
	MatchCombo(deltaTime);
	Super::Tick(deltaTime);
}

void Client::Aoko::Fixed()
{
}

void Client::Aoko::EndPlay()
{
}

void Client::Aoko::NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent)
{
	//std::cout << "Aoko NotifyActorBeginOverlap" << std::endl;
}

void Client::Aoko::NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent)
{
	//std::cout << "Aoko NotifyActorEndOverlap" << std::endl;
}

void Client::Aoko::NotifyActorBlock(::Core::CollisionComponent* pOtherComponent)
{
}

void Client::Aoko::MatchCombo(_float deltaTime)
{
}

void Client::Aoko::LowKickHandler(const InputEvent& inputEvent)
{
	if (!strcmp(_pStateComponent->GetCurrentStateName(),"MiddleKick"))
	{
		return;
	}

	if (_pAnimationComponent->IsFlip())
	{
		_pFootBoxComponent->SetAddOffset({ -80.f, 160.f });
	}
	else
	{
		_pFootBoxComponent->SetAddOffset({ 80.f, 160.f });
	}
	_pFootBoxComponent->SetSize({ 230.f, 220.f });
	_pStateComponent->ChangeState("LowKick");
}

void Client::Aoko::MiddleKickHandler(const InputEvent& inputEvent)
{
	if (!strcmp(_pStateComponent->GetCurrentStateName(),"LowKick"))
	{
		return;
	}

	if(_pAnimationComponent->IsFlip())
	{
		_pFootBoxComponent->SetAddOffset({ -140.f, 100.f });
	}
	else
	{
		_pFootBoxComponent->SetAddOffset({ 140.f, 100.f });
	}
	_pFootBoxComponent->SetSize({ 380.f, 100.f });
	_pStateComponent->ChangeState("MiddleKick");
}

void Client::Aoko::Jump(const InputEvent& inputEvent)
{
	if (_pInputComponent->IsKeyEventTriggerNow(DIK_UP, InputType::PRESS))
	{
		_pMovementComponent->SetInputDirection({ 0.f, -1.f });
	}
	else if (_pInputComponent->IsKeyEventTriggerNow(DIK_UP, InputType::RELEASE))
	{
		_pMovementComponent->SetInputDirection({ 0.f, 0.f });
	}
}

void Client::Aoko::Ducking(const InputEvent& inputEvent)
{
	if (inputEvent.key == DIK_DOWN && inputEvent.type == InputType::HELD)
	{
		_pMovementComponent->SetInputDirection({ 0.f, 1.f });
	}
}

void Client::Aoko::RightMoveHandler(const InputEvent& inputEvent)
{
	if(_pMovementComponent->GetInputDirection() == Mathf::Vector2{ -2.f,0.f })
	{
		return;
	}

	if(_pInputComponent->IsKeyEventTriggeredLessTime(DIK_RIGHT, InputType::RELEASE, 0.18f) &&
		_pInputComponent->IsKeyEventTriggerNow(DIK_RIGHT, InputType::PRESS))
	{
		_pMovementComponent->SetRunning(true);
		_pMovementComponent->SetInputDirection({ 2.f,0.f });
	}
	else if(_pMovementComponent->IsRunning() &&
		_pInputComponent->IsKeyEventTriggerNow(DIK_RIGHT, InputType::HELD))
	{
		_pMovementComponent->SetInputDirection({ 2.f,0.f });
	}
	else
	{
		_pMovementComponent->SetRunning(false);
		_pMovementComponent->SetInputDirection({ 1.f,0.f });
	}

}

void Client::Aoko::LeftMoveHandler(const InputEvent& inputEvent)
{
	if(_pMovementComponent->GetInputDirection() == Mathf::Vector2{ 2.f,0.f })
	{
		return;
	}

	if(_pInputComponent->IsKeyEventTriggeredLessTime(DIK_LEFT, InputType::RELEASE, 0.18f) &&
		_pInputComponent->IsKeyEventTriggerNow(DIK_LEFT, InputType::PRESS))
	{
		_pMovementComponent->SetRunning(true);
		_pMovementComponent->SetInputDirection({ -2.f,0.f });
	}
	else if(_pMovementComponent->IsRunning() &&
		_pInputComponent->IsKeyEventTriggerNow(DIK_LEFT, InputType::HELD))
	{
		_pMovementComponent->SetInputDirection({ -2.f,0.f });
	}
	else
	{
		_pMovementComponent->SetRunning(false);
		_pMovementComponent->SetInputDirection({ -1.f,0.f });
	}
}

void Client::Aoko::StandHandler(const InputEvent& inputEvent)
{
	_pMovementComponent->SetInputDirection({0.f,0.f});
	_pMovementComponent->SetRunning(false);
}

void Client::Aoko::Dead()
{
}

void Client::Aoko::SetPlayClip(_pstring clipName)
{
	_pAnimationComponent->SetPlayClip(clipName);
}
