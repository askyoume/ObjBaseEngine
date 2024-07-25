#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/TextRenderComponent.h"

#include "TestActor.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("BitmapComponent");
	_pBitmapComponent->SetTextures(&_vecTextures);

	_pBoxComponent = AddComponent<::Core::BoxComponent>("BoxComponent");
	_pBoxComponent->SetAddOffset({ 0.f, 0.f });
	_pBoxComponent->SetSize({ 500.f, 150.f });
	_pBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	_pBoxComponent->AddColliderInLayer();

	_pTextRenderComponent = AddComponent<::Core::TextRenderComponent>("TextRenderComponent");
	_pTextRenderComponent->SetFont(L"NameFont");
	_pTextRenderComponent->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	_pTextRenderComponent->SetRelativeScale({ 1.5f, 1.5f });
	_pTextRenderComponent->SetRelativeLocation({ 0.f, 150.f });
	_pTextRenderComponent->SetSize({400.f, 300.f});
	_pTextRenderComponent->AddRenderQueueInLayer();
	_pTextRenderComponent->SetText("[ 로고 마우스 클릭 : 적 재생성 ]");

	_pTargetActor = _pOwnerWorld->FindActor("Neko");
}

void Client::TestActor::Tick(_float deltaSeconds)
{
	Actor::Tick(deltaSeconds);
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::EndPlay()
{
}

void Client::TestActor::NotifyActorBlock(::Core::CollisionComponent* pOtherComponent)
{
}

void Client::TestActor::NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent)
{
	if (*pOtherComponent->GetOwner() == "Mouse")
	{
		if(_pTargetActor->IsDestroyMarked())
		{
			_pOwnerWorld->ReviveActor(_pTargetActor->GetName());
		}
		else
		{
			_pTargetActor->GetRootComponent()->SetRelativeLocation({ 3000.f, -150.f });
		}
	}
}

void Client::TestActor::NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent)
{
}
