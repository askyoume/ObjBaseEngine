#include "ClientWorld.h"
#include "TestActor.h"
#include "TestActor2.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	SpawnActor(OBJECT, "TestActor", TestActor::Create(), Mathf::Vector2{ 960.f , 0 });
	SpawnActor(BACKGROUND, "TestActor2", TestActor2::Create(), Mathf::Vector2{ 960.f, 530.f });
	//test code end

    return true;
}

void Client::ClientWorld::Tick(_float deltaTime)
{
	static float elapsedTime = 0.f;
	elapsedTime += deltaTime;
	::Core::CoreManager* pCoreManager =
		::Core::CoreManager::GetInstance();

	if (elapsedTime > 1.f)
	{
			std::cout << pCoreManager->GetTimeManager()->GetFPS() << std::endl;
			elapsedTime = 0.f;
	}

	World::Tick(deltaTime);
}
