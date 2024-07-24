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
	_pMovementComponent->SetGroundPosition(80.f);

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
	_pAnimationComponent->AddClip("Hit", 0.1f, false);
	_pAnimationComponent->SetOrder(1);
	_pAnimationComponent->SetPlayClip("Idle");

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
	_pTextRenderComponent->SetRelativeLocation({ 0.f, 0.f });
	_pTextRenderComponent->SetSize({400.f, 100.f});
	_pTextRenderComponent->AddRenderQueueInLayer();

}

void Client::Neko::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	_pTextRenderComponent->SetText("AI_State : " + (_bstring)_pAIComponent->GetCurrentStateName());
}

void Client::Neko::Fixed()
{
}

void Client::Neko::EndPlay()
{
}

void Client::Neko::NotifyActorBlock(::Core::CollisionComponent* pOtherComponent)
{
	if ((*pOtherComponent->GetOwner() == "Aoko") &&
	(*pOtherComponent == "FootBoxComponent"))
	{	
		_pAIComponent->ChangeState("AI_Hit");
	}

	if (!_pMovementComponent->IsGrounded() &&
		(*pOtherComponent->GetOwner() == "Aoko") &&
	(*pOtherComponent == "FootBoxComponent"))
	{	
		_pAIComponent->ChangeState("AI_Hit");
		_pMovementComponent->ChangeVelocity().y = -65.f;
	}
	
	if (pOtherComponent->GetOwner()->GetComponent<::Core::StateComponent>("StateComponent")->IsCurrentState("AirLaunch") &&
		(*pOtherComponent == "FootBoxComponent"))
	{
		_pMovementComponent->SetGrounded(false);
		_pMovementComponent->ChangeVelocity().y = -5.f * 300.f;
		_pAIComponent->ChangeState("AI_Hit");
	}
}

void Client::Neko::NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent)
{
	//std::cout << "Neko BeginOverlap" << std::endl;

	if ((*pOtherComponent->GetOwner() == "Aoko") &&
		(*pOtherComponent == "FootBoxComponent"))
	{
		_pAnimationComponent->SetOrder(0);
		//std::cout << "Attacked by Aoko" << std::endl;
	}
}

void Client::Neko::NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent)
{
	//std::cout << "Neko EndOverlap" << std::endl;
}

void Client::Neko::DamageInvoker(int damage)
{
}

int Client::Neko::GetHP() const
{
	return 0;
}

int Client::Neko::GetMaxHP() const
{
	return 0;
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
