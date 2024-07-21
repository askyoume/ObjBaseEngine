//Engine
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"
#include "../../Engine/Headers/CameraActor.h"
#include "../../Engine/Headers/CameraComponent.h"
#include "../../Engine/Headers/StateComponent.h"
//Client
#include "ClientWorld.h"
#include "PlayCameraActor.h"
#include "BackGround.h"
#include "Aoko.h"
#include "Neko.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 16.f);
	//�÷��̾ �ɸ��͸� �����ϸ� �׿� �´� �ɸ��͸� �����ϵ��� �����ؾ���
	//�̰� ���ؼ� ���� ���ѹ����? �ɸ��� Ŭ������ ������ Asset����(json���)�� �����ϰ�, �� ������ �о�ͼ� �����ϴ� ����� ����.
	//�׷���... �ð��� �ǰھ�? ������ ���� �ð��� ����. �׳� ������ ��������.
	SpawnActor(LAYER::FRONTOBJECT, "Aoko", Aoko::Create(), Mathf::Vector2{ 2350.f , 80.f });
	SpawnActor(LAYER::FRONTOBJECT, "Neko", Neko::Create(), Mathf::Vector2{ 3000.f , 80.f });
	//��浵 �׷��� ��.
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 2750.f, -180.f });

	_pAoko = static_cast<Aoko*>(FindActor("Aoko"));
	std::cout << &_pAoko << std::endl;
	_pNeko = static_cast<Neko*>(FindActor("Neko"));
	std::cout << &_pNeko << std::endl;

	SettingCamera(PlayCameraActor::Create());
	SettingCameraPosition(Mathf::Vector2{ 1835.f, -660.f });
	SettingCameraOffset(Mathf::Vector2{0.f, 30.f});
	SetWorldSize(Mathf::Rect{ 0.f, -1580.f, 3500.f, -100.f });

    return isBeginPlayEnd;
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
	_pCoreManager->GetGraphicsPackage()->_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

	::Core::StateComponent* pStateComponent = _pAoko->GetComponent<::Core::StateComponent>("StateComponent");
	_bstring StateName = "Aoko State : \n" + (_bstring)pStateComponent->GetCurrentStateName();
	
	pRenderTarget->DrawTextW(
		StateName,
		StateName.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(100, 500, 500, 100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	::Core::StateComponent* pAIComponent = _pNeko->GetComponent<::Core::StateComponent>("AIComponent");
	_bstring AIStateName = "Neko AI State : \n" + (_bstring)pAIComponent->GetCurrentStateName();

	pRenderTarget->DrawTextW(
		AIStateName,
		AIStateName.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(1300, 600, 1900, 100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	Mathf::Vector2 _distance =
		_pAoko->GetRootComponent()->GetWorldLocation() -
		_pNeko->GetRootComponent()->GetWorldLocation();

	_bstring Distance = "Distance : " + (_bstring)_distance.x;

	pRenderTarget->DrawTextW(
		Distance,
		Distance.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(1600, 1000, 1900, 1100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	_bstring _explanation1 = "[ Left & Right : �̵� | �� ���� ����Ű 2�� : �޸��� ]\n\n[ UP : ���� | A : ��� | S : ���� ]";

	pRenderTarget->DrawTextW(
		_explanation1,
		_explanation1.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(100, 1000, 1500, 1100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	//test code end
}

