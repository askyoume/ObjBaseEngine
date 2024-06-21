#include "ClientWorld.h"
#include "TestActor.h"
#include "TestActor2.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"
#include "../../Engine/Headers/CameraActor.h"
#include "../../Engine/Headers/CameraComponent.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 34.f);

	SpawnActor(OBJECT, "TestActor", TestActor::Create(), Mathf::Vector2{ 960.f , 1080.f });
	SpawnActor(BACKGROUND, "TestActor2", TestActor2::Create(), Mathf::Vector2{ 960.f, 530.f });
	
	SettingTrackingCameraTarget(FindActor("TestActor"));
	SettingCameraOffset(Mathf::Vector2{0.f, 250.f});
	//test code end

    return true;
}

void Client::ClientWorld::Tick(_float deltaTime)
{
	static float elapsedTime = 0.f;
	elapsedTime += deltaTime;

	if (elapsedTime > 1.f)
	{
			std::cout << _pCoreManager->GetTimeManager()->GetFPS() << std::endl;
			elapsedTime = 0.f;
	}

	World::Tick(deltaTime);
}

void Client::ClientWorld::Render(ID2D1RenderTarget* pRenderTarget)
{

	World::Render(pRenderTarget);

	static const WCHAR sc_helloWorld[] = L"Please!!!";
	
	pRenderTarget->DrawTextW(
		sc_helloWorld,
		ARRAYSIZE(sc_helloWorld) - 1,
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(500, 500, 100, 100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	//IDWriteTextLayout* pTextLayout = nullptr;
	//_pCoreManager->GetGraphicsPackage()->_pDWriteFactory->CreateTextLayout(
	//	sc_helloWorld,
	//	ARRAYSIZE(sc_helloWorld) - 1,
	//	_pCoreManager->GetFont(L"DemoFont"),
	//	1000,
	//	1000,
	//	&pTextLayout
	//);
}
