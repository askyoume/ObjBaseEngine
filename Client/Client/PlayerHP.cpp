#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/Mathf.h"

#include "PlayerHP.h"
#include "IPlayerInfo.h"

void Client::PlayerHP::BeginPlay()
{
	Super::BeginPlay();


	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("InnerHP_HUD");
	_pBitmapComponent->SetTextures(&_vecTextures);
	_pBitmapComponent->SetOrder(4);

	_pBitmapComponent2 = AddComponent<::Core::BitmapComponent>("OuterHP_HUD");
	_pBitmapComponent2->SetTextures(&_vecTextures);
	_pBitmapComponent2->SetBitmapIndex(1);
	_pBitmapComponent2->SetCenterAlignment(false);
	_pBitmapComponent2->SetRelativeLocation({ -200.f, -10.f });
	_pBitmapComponent2->SetOrder(5);
	_pBitmapComponent2->SetTextureClipping(true);
	_textureRect = _pBitmapComponent2->GetTextureRect();
	_pBitmapComponent2->SetTextureClippingRect(_textureRect);


	_pRootComponent->SetRelativeScale({ 1.5f, 1.5f });
}

void Client::PlayerHP::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if(_pPlayerInfo)
	{
		_currentHP = _pPlayerInfo->GetHP();
		if(_previousHP != _currentHP)
		{
			_currentHPFraction = static_cast<float>(_currentHP) * _maxHPUnit;
			_textureRect.right *= _currentHPFraction;
			_pBitmapComponent2->SetTextureClippingRect(_textureRect);
		}
		_previousHP = _currentHP;
	}
}

void Client::PlayerHP::Fixed()
{

}

void Client::PlayerHP::EndPlay()
{
}

void Client::PlayerHP::SetPlayerInfo(::Core::Actor* pPlayerInfo)
{
	_pPlayerInfo = dynamic_cast<IPlayerInfo*>(pPlayerInfo);
	_currentHP = _pPlayerInfo->GetHP();
	_previousHP = _currentHP;
	_maxHP = _pPlayerInfo->GetMaxHP();
	_maxHPUnit = 1.f / static_cast<float>(_maxHP);

	_currentHPFraction = static_cast<float>(_currentHP) * _maxHPUnit;
	_textureRect.right *= _currentHPFraction;
	_pBitmapComponent2->SetTextureClippingRect(_textureRect);
}

void Client::PlayerHP::SwitchPlayer(_uint playerID)
{
	if(playerID == PlayerID_Two)
	{
		_pBitmapComponent2->SetRelativeLocation({ -204.f, -10.f });
		_pBitmapComponent2->SetFlip(true);
	}
}
