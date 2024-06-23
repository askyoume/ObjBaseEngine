#include "ClientWorld.h"
#include "TestActor.h"
#include "TestActor2.h"
#include "BackGround.h"
#include "Moon.h"
#include "NightSky.h"
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

	SpawnActor(LAYER::OBJECT, "TestActor", TestActor::Create(), Mathf::Vector2{ -2000.f , 0.f });
	SpawnActor(LAYER::BACKOBJECT, "TestActor2", TestActor2::Create(), Mathf::Vector2{ 0.f, 0.f });
	SpawnActor(LAYER::BACKGROUND, "NightSky", NightSky::Create(), Mathf::Vector2{ 0.f, 0.f });
	SpawnActor(LAYER::BACKGROUND, "Moon", Moon::Create(), Mathf::Vector2{ 300.f, -450.f });
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 240.f, -180.f });

	TestActor2* _pTestActor2 = static_cast<TestActor2*>(FindActor("TestActor2"));
	TestActor* _pTestActor = static_cast<TestActor*>(FindActor("TestActor"));

	__Khala->DefineNerveCord("Fire", [_pTestActor](__KhalaArgs args)
		{
			if (_pTestActor->GetRootComponent()->GetWorldLocation().x > 0)
			{
				_pTestActor->Fire();

				return true; //이벤트 등록할 람다식으로 이루어진 임시객체는 반드시 bool을 반환해야함
							//리턴값을 강제하는 이유는 이벤트의 동작이 성공적으로 이루어졌는지 확인하기 위함
							//또한 이벤트를 설계할 때 조건에 따른 이벤트 동작을 위해 사용됨
			}

			return false;
		});
	
	SettingTrackingCameraTarget(FindActor("TestActor"));
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
