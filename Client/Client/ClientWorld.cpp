#include "ClientWorld.h"
#include "TestActor.h"
#include "TestActor2.h"
#include "BackGround.h"
#include "Moon.h"
#include "NightSky.h"
#include "Character.h"
//Engine
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"
#include "../../Engine/Headers/CameraActor.h"
#include "../../Engine/Headers/CameraComponent.h"
#include "../../Engine/Headers/KhalaSystem.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 34.f);

	SpawnActor(LAYER::OBJECT,"Character", Charactor::Create(), Mathf::Vector2{ -2000.f , 0.f });
	//SpawnActor(LAYER::OBJECT, "TestActor", TestActor::Create(), Mathf::Vector2{ -2000.f , 0.f });
	SpawnActor(LAYER::BACKOBJECT, "TestActor2", TestActor2::Create(), Mathf::Vector2{ 0.f, 0.f });
	SpawnActor(LAYER::BACKGROUND, "NightSky", NightSky::Create(), Mathf::Vector2{ 0.f, 0.f });
	SpawnActor(LAYER::BACKGROUND, "Moon", Moon::Create(), Mathf::Vector2{ 300.f, -450.f });
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 240.f, -180.f });

	TestActor2* _pTestActor2 = static_cast<TestActor2*>(FindActor("TestActor2"));

	__Khala->DefineNerveCord("OuterMove", [](__KhalaArgs args)
		{
			::Core::Actor* pActor = __KhalaCast<::Core::Actor*>(args[0]);
			float x = __KhalaCast<float>(args[1]);
			float y = __KhalaCast<float>(args[2]);

			pActor->GetRootComponent()->AddRelativeLocation(Mathf::Vector2{ x, y });

			return true;

		});
	
	SettingTrackingCameraTarget(FindActor("Character"));
	SettingCameraOffset(Mathf::Vector2{0.f, 250.f});
	SetWorldSize(Mathf::Rect{ -3500.f, -1580.f, 1580.f, -100.f });
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
	//test code
	//static const WCHAR sc_helloWorld[] = L"Please!!!";
	//
	//pRenderTarget->DrawTextW(
	//	sc_helloWorld,
	//	ARRAYSIZE(sc_helloWorld) - 1,
	//	_pCoreManager->GetFont(L"DemoFont"),
	//	D2D1::RectF(500, 500, 100, 100),
	//	_pCoreManager->GetGraphicsPackage()->_pBrush
	//);

	//IDWriteTextLayout* pTextLayout = nullptr;
	//_pCoreManager->GetGraphicsPackage()->_pDWriteFactory->CreateTextLayout(
	//	sc_helloWorld,
	//	ARRAYSIZE(sc_helloWorld) - 1,
	//	_pCoreManager->GetFont(L"DemoFont"),
	//	1000,
	//	1000,
	//	&pTextLayout
	//);
	// 
	//test code end
}

