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

	pInputComponent->BindInputEvent(DIP_A, InputType::PRESS, [&](const InputEvent& inputEvent)
		{
			pInputComponent->SetVibration(0.f, 1.f);
			Fire();
		});

	pInputComponent->BindInputEvent(DIP_A, InputType::RELEASE, [&](const InputEvent& inputEvent)
		{
			pInputComponent->SetVibration(0.f, 0.f);
		});

	pInputComponent->BindInputEvent(DIK_AXIS, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move((float)inputEvent.x, (float)-inputEvent.y);
		});

	pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(0, inputEvent.value);
		});

	pInputComponent->AttachToInputManager();

	pBitmapComponent->SetTextures(&_vecTextures);

	pBitmapComponent->AddRenderQueueInLayer();
}

void Client::TestActor::Tick(_float deltaTime)
{
	std::cout << _pRootComponent->GetWorldLocation().x << " " 
		<< _pRootComponent->GetWorldLocation().y << std::endl;

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
