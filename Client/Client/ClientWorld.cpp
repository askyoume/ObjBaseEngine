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
#include "Neko.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 34.f);

	SpawnActor(LAYER::FRONTOBJECT, "Aoko", Aoko::Create(), Mathf::Vector2{ 1750.f , 80.f });
	SpawnActor(LAYER::FRONTOBJECT, "Neko", Neko::Create(), Mathf::Vector2{ 1900.f , 80.f });
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 2750.f, -180.f });

	_pAoko = static_cast<Aoko*>(FindActor("Aoko"));
	_pNeko = static_cast<Neko*>(FindActor("Neko"));

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

	::Core::StateComponent* pAIComponent = _pNeko->GetComponent<::Core::StateComponent>("AIComponent");
	_bstr_t AIStateName = "Neko AI State : \n" + (_bstr_t)pAIComponent->GetCurrentStateName();

	pRenderTarget->DrawTextW(
		AIStateName,
		AIStateName.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(1100, 600, 1500, 100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	Mathf::Vector2 _distance =
		_pAoko->GetRootComponent()->GetWorldLocation() -
		_pNeko->GetRootComponent()->GetWorldLocation();

	_bstr_t Distance = "Distance : " + (_bstr_t)_distance.x;

	pRenderTarget->DrawTextW(
		Distance,
		Distance.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(1600, 1000, 1900, 1100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	//test code end
}

