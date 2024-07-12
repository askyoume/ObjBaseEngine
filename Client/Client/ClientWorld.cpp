//Engine
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"
#include "../../Engine/Headers/CameraActor.h"
#include "../../Engine/Headers/CameraComponent.h"
#include "../../Engine/Headers/StateComponent.h"
//Client
#include "ClientWorld.h"
#include "BackGround.h"
#include "Aoko.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 34.f);

	SpawnActor(LAYER::FRONTOBJECT, "Aoko", Aoko::Create(), Mathf::Vector2{ 1750.f , 80.f });
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 2750.f, -180.f });

	_pAoko = static_cast<Aoko*>(FindActor("Aoko"));

	//TODO: Debug Code
	SettingTrackingCameraTarget(FindActor("Aoko"));
	SettingCameraOffset(Mathf::Vector2{0.f, 30.f});
	SetWorldSize(Mathf::Rect{ 0.f, -1580.f, 3500.f, -100.f });
	//1920,1480
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

	pRenderTarget->SetTransform(Matx::Identity);

	::Core::StateComponent* pStateComponent = _pAoko->GetComponent<::Core::StateComponent>("StateComponent");
	_bstr_t StateName = "Aoko State : \n" + (_bstr_t)pStateComponent->GetCurrentStateName();
	
	pRenderTarget->DrawTextW(
		StateName,
		StateName.length(),
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
	// 
	//test code end
}

