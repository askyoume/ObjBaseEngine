#include "TestActor.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("BitmapComponent");

	_pInputComponent->BindInputEvent(DIP_RX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Rotate(inputEvent.value);
		});

	_pInputComponent->BindInputEvent(DIP_RT, InputType::TRIGGER, [&](const InputEvent& inputEvent)
		{
			_pInputComponent->SetVibration(0, inputEvent.value);

			Fire();
		});

	_pInputComponent->BindInputEvent(DIP_LX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(inputEvent.value, 0);
		});

	_pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(0, inputEvent.value);
		});

	_pInputComponent->AttachToInputManager();

	_pBitmapComponent->SetTextures(&_vecTextures);
}

void Client::TestActor::Tick(_float deltaTime)
{
	//std::cout << _pRootComponent->GetWorldLocation().x << " " 
	//	<< _pRootComponent->GetWorldLocation().y << std::endl;

	Actor::Tick(deltaTime);
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::EndPlay()
{
}
//test code
void Client::TestActor::Fire()
{
	std::cout << "Fire" << std::endl;
}

void Client::TestActor::Rotate(float degree)
{
	_pRootComponent->AddRelativeRotation(degree);
}

void Client::TestActor::Move(float x, float y)
{
	_pRootComponent->AddRelativeLocation(Mathf::Vector2{x, y});
}
//test code end
