#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"

#include "PlayerHP.h"
#include "IPlayerInfo.h"

void Client::PlayerHP::BeginPlay()
{
	Super::BeginPlay();

	_pPlayerInfo = dynamic_cast<IPlayerInfo*>(_pOwnerWorld->FindActor("Aoko"));
	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("InnerHP_HUD");
	_pBitmapComponent->SetTextures(&_vecTextures);
	_pBitmapComponent->SetOrder(2);

	_pBitmapComponent2 = AddComponent<::Core::BitmapComponent>("OuterHP_HUD");
	_pBitmapComponent2->SetTextures(&_vecTextures);
	_pBitmapComponent2->SetBitmapIndex(1);
	_pBitmapComponent2->SetCenterAlignment(false);
	_pBitmapComponent2->SetRelativeLocation({ -200.f, -10.f });
	_pBitmapComponent2->SetRelativeScale({ 1.f, 1.f });
	_pBitmapComponent2->SetOrder(1);
	//_pBitmapComponent2->SetFlip(true);

	_pRootComponent->SetRelativeScale({ 1.5f, 1.8f });

	_currentHP = _pPlayerInfo->GetHP();
	_maxHP = _pPlayerInfo->GetMaxHP();
	_maxHPUnit = 1.f / static_cast<float>(_maxHP);
}

void Client::PlayerHP::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	_currentHP = _pPlayerInfo->GetHP();
	_currentHPPercent = static_cast<float>(_currentHP) * _maxHPUnit;

	_pBitmapComponent2->SetRelativeScale({ _currentHPPercent, 1.f });
}

void Client::PlayerHP::Fixed()
{

}

void Client::PlayerHP::EndPlay()
{
}
