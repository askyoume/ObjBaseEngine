#include "TestActor2.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"

void Client::TestActor2::BeginPlay()
{
	Actor::BeginPlay();

	AddComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

	pBitmapComponent->SetTextures(&_vecTextures);
	pBitmapComponent->SetRelativeScale(Mathf::Vector2(5.f, 5.f));
	pBitmapComponent->AddRenderQueueInLayer();

	//Mathf::Rect worldSize = pBitmapComponent->GetTransformedTextureRect();
}

void Client::TestActor2::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);
	//::Core::BitmapComponent* pBitmapComponent =
	//	GetComponent<::Core::BitmapComponent>("BitmapComponent");

	//Mathf::Rect worldSize = pBitmapComponent->GetTransformedTextureRect();
	////_pOwnerWorld->SetWorldSize(worldSize);
}

void Client::TestActor2::Fixed()
{

}

void Client::TestActor2::EndPlay()
{
}
