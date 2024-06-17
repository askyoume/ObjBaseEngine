#include "TestActor.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	AddComponent<::Core::InputComponent>("InputComponent");
	AddComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::InputComponent* pInputComponent = 
		GetComponent<::Core::InputComponent>("InputComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

	pInputComponent->BindInputEvent(DIP_RX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Rotate(inputEvent.value);
		});

	pInputComponent->BindInputEvent(DIP_RT, InputType::TRIGGER, [&](const InputEvent& inputEvent)
		{
			XINPUT_VIBRATION vibration{
				0, 
				static_cast<WORD>(inputEvent.value * USHRT_MAX)
			};

			XInputSetState(0, &vibration);

			Fire();
		});

	pInputComponent->BindInputEvent(DIP_RT, InputType::RELEASE, [&](const InputEvent& inputEvent)
		{
			XINPUT_VIBRATION vibration{ 0, 0 };
			XInputSetState(0, &vibration);
		});

	pInputComponent->BindInputEvent(DIP_LX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(inputEvent.value, 0);
		});

	pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(0, -inputEvent.value);
		});

	pInputComponent->AttachToInputManager();

	pBitmapComponent->SetTextures(&_vecTextures);

	pBitmapComponent->AddRenderQueueInLayer();
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
void Client::TestActor::Remove()
{
	for (auto& component : _vecComponents)
		SafeDelete(component);

	_vecComponents.clear();
}
