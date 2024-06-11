#include "TestActor.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	::Core::CoreManager* pCore = ::Core::CoreManager::GetInstance();

	CreateComponent<::Core::InputComponent>("InputComponent");
	CreateComponent<::Core::BitmapComponent>("BitmapComponent");

	::Core::InputComponent* pInputComponent = 
		GetComponent<::Core::InputComponent>("InputComponent");

	::Core::BitmapComponent* pBitmapComponent =
		GetComponent<::Core::BitmapComponent>("BitmapComponent");

	pInputComponent->BindInputEvent(DIP_A, InputType::PRESS, [&](const InputEvent& inputEvent)
		{
			Fire();
		});

	pInputComponent->AttachToInputManager();

	pBitmapComponent->SetTextures(&_vecTextures);
}

void Client::TestActor::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::Render(ID2D1RenderTarget* pRenderTarget)
{
	Actor::Render(pRenderTarget);
}

void Client::TestActor::EndPlay()
{
}
//test code
void Client::TestActor::Fire()
{
	std::cout << "Fire" << std::endl;
	//OnDestroyMark(true);
	//std::cout << (IsDestroyMarked() ? "ture" : "false") << std::endl;
}
//test code end
void Client::TestActor::Remove()
{
	for (auto& component : _vecComponents)
		SafeDelete(component);

	_vecComponents.clear();
}
