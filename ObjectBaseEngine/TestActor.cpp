#include "TestActor.h"
#include "Actor.h"
#include "InputComponent.h"
#include "CoreManager.h"

void Game::TestActor::BeginPlay()
{
	::Core::CoreManager* pCore = ::Core::CoreManager::GetInstance();

	CreateComponent<::Core::InputComponent>("InputComponent");
	::Core::InputComponent* pInputComponent = GetComponent<::Core::InputComponent>("InputComponent");
	DIJOYSTATE2 GamePadState{};

	pInputComponent->BindInputEvent(DIP_AXIS_LX, InputType::MOVE, [&](const InputEvent& inputEvent)
		{
			std::cout << "AXIS_X" << std::endl;
			Fire();
		});

	pInputComponent->AttachToInputManager();
}

void Game::TestActor::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);
}

void Game::TestActor::Fixed()
{
}

void Game::TestActor::Render(ID2D1RenderTarget* pRenderTarget)
{
}

void Game::TestActor::EndPlay()
{
}
//test code
void Game::TestActor::Fire()
{
	std::cout << "Fire" << std::endl;
	//OnDestroyMark(true);
	//std::cout << (IsDestroyMarked() ? "ture" : "false") << std::endl;
}
//test code end
void Game::TestActor::Remove()
{
	for (auto& component : _vecComponents)
		SafeDelete(component);

	_vecComponents.clear();
}
