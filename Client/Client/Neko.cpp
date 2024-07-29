#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/TextRenderComponent.h"

#include "Neko.h"
#include "Aoko.h"
#include "AIMovementFSMContainer.h"

void Client::Neko::BeginPlay()
{
	Super::BeginPlay();

	_pAnimationComponent = AddComponent<::Core::AnimationComponent>("AnimationComponent");
	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pTextRenderComponent = AddComponent<::Core::TextRenderComponent>("TextRenderComponent");
	_pMovementComponent = AddComponent<::Core::MovementComponent>("MovementComponent");
	_pMovementComponent->SetGroundPosition(-130.f);

	_pAnimationComponent->AddClip("Idle", 0.1f, true);
	_pAnimationComponent->AddClip("Move", 0.1f, true);
	_pAnimationComponent->AddClip("BackMove", 0.1f, true);
	//_pAnimationComponent->AddClip("Jump", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToBackMove", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToRuning", 0.1f, false);
	_pAnimationComponent->AddClip("ReadyToIdle", 0.1f, false);
	_pAnimationComponent->AddClip("Running", 0.1f, true);
	_pAnimationComponent->AddClip("LowKick", 0.1f, false);
	_pAnimationComponent->AddClip("Hit", 0.07f, false);
	_pAnimationComponent->AddClip("Dead", 0.1f, false);
	_pAnimationComponent->SetOrder(1);
	_pAnimationComponent->SetPlayClip("Idle");

	_pRootComponent->SetRelativeScale({1.5f, 1.5f});

	_pInputComponent->AttachToInputManager();

	_pBoxComponent = AddComponent<::Core::BoxComponent>("BoxComponent");
	_pBoxComponent->SetAddOffset({ 0.f, 150.f });
	_pBoxComponent->SetSize({ 90.f, 300.f });
	_pBoxComponent->SetCollisionType(Collision::COLLISION_BLOCK);
	_pBoxComponent->AddColliderInLayer();

	_pAIComponent = AddComponent<::Core::StateComponent>("AIComponent");
	_pAIComponent->AddContainer<AIMovementFSMContainer>();

	_pTextRenderComponent->SetFont(L"NameFont");
	_pTextRenderComponent->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	_pTextRenderComponent->SetRelativeLocation({ 0.f, 100.f });
	_pTextRenderComponent->SetSize({400.f, 200.f});
	_pTextRenderComponent->AddRenderQueueInLayer();

}

void Client::Neko::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	_pTextRenderComponent->SetText("AI_State : " + (_bstring)_pAIComponent->GetCurrentStateName());

	if(_isDead)
	{
		_elapsedTime += deltaSeconds;
	}

	if (_elapsedTime >= 3.f)
	{
		OnDestroyMark(true);
	}
}

void Client::Neko::Fixed()
{
	if(!_pTargetAnimationComponent || !_pTargetStateComponent)
		return;

	if (_pAIComponent->IsCurrentState("AI_DEAD") &&
		_pTargetAnimationComponent->IsFrameEnd())
	{
		_isDead = true;
	} 
	else if(0 >= _currentHP && !_isDead)
	{
		_pAIComponent->ForceCheckTransition("AI_DEAD");
	}

}

void Client::Neko::EndPlay()
{
}

void Client::Neko::NotifyActorBlock(::Core::CollisionPackage Components)
{
	if((*Components.otherComponent->GetOwner() == "Aoko") &&
		!_pTargetAnimationComponent)
	{
		_pTargetAnimationComponent = Components.otherComponent->GetOwner()->GetComponent<::Core::AnimationComponent>("AnimationComponent");
		_pTargetStateComponent = Components.otherComponent->GetOwner()->GetComponent<::Core::StateComponent>("StateComponent");
	}

	if ((*Components.otherComponent->GetOwner() == "Aoko") &&
		(*Components.otherComponent == "FootBoxComponent"))
	{	
		_pAIComponent->ChangeState("AI_Hit");
		//DamageInvoker(10);
	}

	if (!_pMovementComponent->IsGrounded() &&
		(*Components.otherComponent->GetOwner() == "Aoko") &&
		(*Components.otherComponent == "FootBoxComponent"))
	{	
		_pAIComponent->ChangeState("AI_Hit");
		_pMovementComponent->ChangeVelocity().y = -60.f;
		//DamageInvoker(14);
	}
	
	if ((*Components.otherComponent->GetOwner() == "Aoko") &&
		(*Components.otherComponent == "FootBoxComponent") &&
		_pTargetStateComponent->IsCurrentState("AirLaunch"))
	{
		_pMovementComponent->SetGrounded(false);
		_pMovementComponent->ChangeVelocity().y = -5.f * 300.f;
		_pAIComponent->ChangeState("AI_Hit");
		//DamageInvoker(17);
	}
}

void Client::Neko::NotifyActorBeginOverlap(::Core::CollisionPackage Components)
{
	std::cout << "Neko BeginOverlap" << std::endl;

	if ((*Components.otherComponent->GetOwner() == "Aoko") &&
		(*Components.otherComponent == "FootBoxComponent"))
	{
		_pAnimationComponent->SetOrder(0);
	}
}

void Client::Neko::NotifyActorEndOverlap(::Core::CollisionPackage Components)
{
	//std::cout << "Neko EndOverlap" << std::endl;
}

void Client::Neko::ReviveInitialize()
{
	_pAIComponent->ChangeState("AI_IDLE");
	_pBoxComponent->SetCollisionType(Collision::COLLISION_BLOCK);
	_pRootComponent->SetRelativeLocation({ 3000.f, -130.f });
	_currentHP = _maxHP;
	_elapsedTime = 0.f;
	_isDead = false;
}

void Client::Neko::DamageInvoker(int damage)
{
	_currentHP -= damage;
}

bool Client::Neko::IsHit() const
{
	return _pAIComponent->IsCurrentState("AI_Hit");
}

int Client::Neko::GetHP() const
{
	return _currentHP;
}

int Client::Neko::GetMaxHP() const
{
	return _maxHP;
}

int Client::Neko::GetGauge() const
{
	return 0;
}

int Client::Neko::GetMaxGauge() const
{
	return 0;
}

Client::Neko* Client::Neko::Create()
{
	return new Neko;
}
