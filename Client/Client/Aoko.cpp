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
	_pAnimationComponent->AddClip("ReadyToRuning", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToIdle", 0.1f, false);
	_pAnimationComponent->AddClip("Runing", 0.1f, true);
	_pAnimationComponent->AddClip("MiddleKick", 0.1f, false);

	_pInputComponent->BindAction(DIP_LX, InputType::AXIS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::PRESS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_LEFT, InputType::PRESS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::HELD, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_LEFT, InputType::HELD, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_UP, InputType::PRESS, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_DOWN, InputType::HELD, this, &Aoko::Move);
	_pInputComponent->BindAction(DIK_RIGHT, InputType::RELEASE, this, &Aoko::MoveHandler);
	_pInputComponent->BindAction(DIK_LEFT, InputType::RELEASE, this, &Aoko::MoveHandler);
	_pInputComponent->BindAction(DIK_UP, InputType::RELEASE, this, &Aoko::MoveHandler);
	_pInputComponent->BindAction(DIK_DOWN, InputType::RELEASE, this, &Aoko::MoveHandler);
	_pInputComponent->BindAction(DIK_A, InputType::PRESS, this, &Aoko::Attack);
	_pInputComponent->AttachToInputManager();

	_pStateComponent = AddComponent<::Core::StateComponent>("StateComponent");
	_pStateComponent->AddContainer<ClientFSMContainer>();

	_pBodyBoxComponent = AddComponent<::Core::BoxComponent>("BodyBoxComponent");
	_pBodyBoxComponent->SetAddOffset({ 0.f, 100.f });
	_pBodyBoxComponent->SetSize({ 100.f, 400.f });
	_pBodyBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	_pBodyBoxComponent->AddColliderInLayer();

	_pFootBoxComponent = AddComponent<::Core::BoxComponent>("FootBoxComponent");
	_pFootBoxComponent->SetAddOffset({ 0.f, 200.f });
	_pFootBoxComponent->SetSize({ 400.f, 100.f });
	_pFootBoxComponent->SetCollisionType(Collision::COLLISION_IGNORE);
	_pFootBoxComponent->AddColliderInLayer();

	_pAnimationComponent->SetPlayClip("Idle");
}

void Client::Aoko::Tick(_float deltaTime)
{
	MatchCombo(deltaTime);
	Super::Tick(deltaTime);

	if (!strcmp(_pStateComponent->GetCurrentStateName(),"IDLE"))
	{
		_pBodyBoxComponent->SetSize({ 100.f, 400.f });
	}
	else if(!strcmp(_pStateComponent->GetCurrentStateName(),"MOVE"))
	{
		_pBodyBoxComponent->SetSize({ 120.f, 400.f });
	}
	else if(!strcmp(_pStateComponent->GetCurrentStateName(),"RUNING"))
	{
		_pBodyBoxComponent->SetSize({ 280.f, 400.f });
	}
}

void Client::Aoko::Fixed()
{
}

void Client::Aoko::EndPlay()
{
}

void Client::Aoko::NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent)
{
	std::cout << "Aoko NotifyActorBeginOverlap" << std::endl;
}

void Client::Aoko::NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent)
{
	std::cout << "Aoko NotifyActorEndOverlap" << std::endl;
}

void Client::Aoko::NotifyActorBlock(::Core::CollisionComponent* pOtherComponent)
{
}

void Client::Aoko::MatchCombo(_float deltaTime)
{
	_comboTime += deltaTime;

	if (_inputQueue.size() > 12)
	{
		_inputQueue.pop_front();
	}

	if (_inputQueue.size() > 3)
	{
		//if (_inputQueue[0].key == DIK_RIGHT &&
		//	_inputQueue[1].key == DIK_RIGHT)
		//{
		//	_pMovementComponent->SetRunning(true);
		//}
	}

	//if (_comboTime > 0.5f)
	//{
	//	_comboTime = 0.f;
	//	_inputQueue.clear();
	//}
}

InputEvent Client::Aoko::GetPrevInputEvent()
{
	//std::cout << "Key : " << _inputQueue.front().key << std::endl;
	//std::cout << "Type : " << (int)_inputQueue.front().type << std::endl;
	if (_inputQueue.size() < 2)
	{
		return _inputQueue.back();
	}
	return _inputQueue[_inputQueue.size() - 2];
}

void Client::Aoko::Attack(const InputEvent& inputEvent)
{
	//debug code
	OnDestroyMark(true);
}

void Client::Aoko::Move(const InputEvent& inputEvent)
{
	//_direction.x = inputEvent.value;
	//_direction.y = inputEvent.value;

	if(inputEvent.type == InputType::PRESS || inputEvent.type == InputType::AXIS)
	{
		//std::cout << inputEvent.key << std::endl;
		_inputQueue.push_back(inputEvent);
	}

	if(inputEvent.key == DIP_LX && inputEvent.type == InputType::AXIS)
	{
		if(	inputEvent.value > 0.7f || inputEvent.value < -0.7f )
		_pMovementComponent->SetInputDirection({ inputEvent.value, 0.f });
		else
		_pMovementComponent->SetInputDirection({ 0.f, 0.f });
	}

	if (inputEvent.key == DIK_LEFT && inputEvent.type == InputType::HELD)
	{
		if(GetPrevInputEvent().key == DIK_LEFT && GetPrevInputEvent().type == InputType::RELEASE)
		{
			_pMovementComponent->SetRunning(true);
			_pMovementComponent->SetInputDirection({ -2.f,0.f });
		}
		else
		{
			_pMovementComponent->SetRunning(false);
			_pMovementComponent->SetInputDirection({ -1.f,0.f });
		}
	}
	if (inputEvent.key == DIK_RIGHT && inputEvent.type == InputType::HELD)
	{
		if(GetPrevInputEvent().key == DIK_RIGHT && GetPrevInputEvent().type == InputType::RELEASE)
		{
			_pMovementComponent->SetRunning(true);	
			_pMovementComponent->SetInputDirection({ 2.f,0.f });
		}
		else
		{
			_pMovementComponent->SetRunning(false);
			_pMovementComponent->SetInputDirection({ 1.f,0.f });
		}
	}

	if (inputEvent.key == DIK_UP && inputEvent.type == InputType::PRESS)
	{
		_pMovementComponent->SetInputDirection({ 0.f, -1.f });
	}
	else if (inputEvent.key == DIK_DOWN && inputEvent.type == InputType::HELD)
	{
		_pMovementComponent->SetInputDirection({ 0.f, 1.f });
	}
}

void Client::Aoko::MoveHandler(const InputEvent& inputEvent)
{
	if (inputEvent.type == InputType::RELEASE)
	{
		std::cout << inputEvent.key << std::endl;
		_inputQueue.push_back(inputEvent);
		_pMovementComponent->SetInputDirection({0.f,0.f});
		_pMovementComponent->SetRunning(false);
	}
}

void Client::Aoko::Dead()
{
}

void Client::Aoko::SetPlayClip(_pstring clipName)
{
	_pAnimationComponent->SetPlayClip(clipName);
}
