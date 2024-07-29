#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/BoxComponent.h"
#include "../../Engine/Headers/InputComponent.h"

#include "Timer.h"

void Client::Timer::BeginPlay()
{
	Super::BeginPlay();

	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("InnerPlate");
	_pBitmapComponent->SetTextures(&_vecTextures);
	_pBitmapComponent->SetOrder(1);

	_pBitmapComponent2 = AddComponent<::Core::BitmapComponent>("TimerFrontNumber");
	_pBitmapComponent2->SetTextures(&_vecTextures);
	_pBitmapComponent2->SetBitmapIndex(TimerNumberTexture_Infinity);
	_pBitmapComponent2->SetRelativeLocation({ 162.f, 35.f });
	_pBitmapComponent2->SetOrder(2);

	_pBitmapComponent3 = AddComponent<::Core::BitmapComponent>("TimerBackNumber");
	_pBitmapComponent3->SetTextures(&_vecTextures);
	_pBitmapComponent3->SetBitmapIndex(TimerNumberTexture_0);
	_pBitmapComponent3->SetRelativeLocation({ 192.f, 35.f });
	_pBitmapComponent3->SetOrder(2);
	_pBitmapComponent3->SetVisible(false);

	_pBoxComponent = AddComponent<::Core::BoxComponent>("TimerBox");
	_pBoxComponent->SetAddOffset({ 0.f, 0.f });
	_pBoxComponent->SetSize({ 500.f, 150.f });
	_pBoxComponent->SetCollisionType(Collision::COLLISION_OVERLAP);
	_pBoxComponent->AddColliderInLayer();

	_pInputComponent = AddComponent<::Core::InputComponent>("TimerInput");
	_pInputComponent->BindInputEvent(DIK_END, InputType::PRESS, [](const InputEvent inputEvent){
				::Core::CoreManager* pCoreManager = ::Core::CoreManager::GetInstance();
				pCoreManager->SetTimeScale(0.3f);
		});

	_pInputComponent->BindInputEvent(DIK_HOME, InputType::PRESS, [](const InputEvent inputEvent) {
				::Core::CoreManager* pCoreManager = ::Core::CoreManager::GetInstance();
				pCoreManager->SetTimeScale(1.f);
		});
	_pInputComponent->AttachToInputManager();

	_pRootComponent->SetRelativeScale({ 1.54f, 1.5f });
}

void Client::Timer::Tick(_float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (_isTimerOn)
	{
		if(!_pBitmapComponent3->IsVisible())
		{
			_pBitmapComponent3->SetVisible(true);
		}

		_elapsedTime += deltaSeconds;

		if (_elapsedTime >= 1.f)
		{
			_remainTime--;
			_elapsedTime -= _elapsedTime;
		}

		if (0.f >= _remainTime)
		{
			_isTimeOver = true;
			_remainTime = 0.f;
		}

		int remainTimeInt = static_cast<int>(_remainTime);

		std::div_t result = std::div(remainTimeInt, 10);
		int firstNumber = result.quot; // ¸ò
		int secondNumber = result.rem; // ³ª¸ÓÁö

		_pBitmapComponent2->SetBitmapIndex(firstNumber + TimerNumberTexture_0);
		_pBitmapComponent3->SetBitmapIndex(secondNumber + TimerNumberTexture_0);
	}
	else
	{
		if(_pBitmapComponent3->IsVisible())
		{
			_pBitmapComponent3->SetVisible(false);
			_pBitmapComponent2->SetBitmapIndex(TimerNumberTexture_Infinity);
		}
	}
}

void Client::Timer::Fixed()
{
}

void Client::Timer::EndPlay()
{
}

void Client::Timer::NotifyActorBlock(::Core::CollisionPackage Components)
{
}

void Client::Timer::NotifyActorBeginOverlap(::Core::CollisionPackage Components)
{
	if (*Components.otherComponent->GetOwner() == "Mouse")
	{
		if(_isTimerOn)
		{
			_isTimerOn = false;
		}
		else
		{
			_isTimerOn = true;
			ResetTimer();
		}
	}
}

void Client::Timer::NotifyActorEndOverlap(::Core::CollisionPackage Components)
{
}
