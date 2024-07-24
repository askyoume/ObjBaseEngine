//Engine
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/TimeManager.h"
#include "../../Engine/Headers/CameraActor.h"
#include "../../Engine/Headers/CameraComponent.h"
#include "../../Engine/Headers/StateComponent.h"
#include "../../Engine/Headers/MovementComponent.h"
//Client
#include "ClientWorld.h"
#include "PlayCameraActor.h"
#include "BackGround.h"
#include "Aoko.h"
#include "Neko.h"
#include "TestActor.h"
#include "PlayerHP.h"
#include "PlayerOneFace.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 16.f);
	_pCoreManager->LoadFont(L"NameFont", L"Client/Resources/Font/EFKratos.ttf", 12.f);
	//플레이어가 케릭터를 선택하면 그에 맞는 케릭터를 생성하도록 수정해야함
	//이걸 위해서 가장 편한방법은? 케릭터 클래스의 정보를 Asset파일(json기반)로 저장하고, 그 정보를 읽어와서 생성하는 방법이 있음.
	//그런데... 시간이 되겠어? ㅋㅋㅋ 이제 시간이 없어. 그냥 빠르게 만들어야지.
	SpawnActor(LAYER::FRONTOBJECT, "Aoko", Aoko::Create(), Mathf::Vector2{ 2350.f , 80.f });
	SpawnActor(LAYER::FRONTOBJECT, "Neko", Neko::Create(), Mathf::Vector2{ 3000.f , 80.f });
	SpawnActor(LAYER::UI, "PlayerOneHP", PlayerHP::Create(), Mathf::Vector2{ 520.f , 110.f });
	SpawnActor(LAYER::UI, "PlayerOneFace", PlayerOneFace::Create(), Mathf::Vector2{ 330.f , 110.f });

	//배경도 그래야 함.
	SpawnActor(LAYER::UI, "TestActor", TestActor::Create(), Mathf::Vector2{ 960.f , 900.f });
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 2750.f, -180.f });

	_pAoko = static_cast<Aoko*>(FindActor("Aoko"));
	_pNeko = static_cast<Neko*>(FindActor("Neko"));

	SettingCamera(PlayCameraActor::Create());
	SettingCameraPosition(Mathf::Vector2{ 1835.f, -560.f });
	SettingCameraOffset(Mathf::Vector2{0.f, 30.f});
	SetWorldSize(Mathf::Rect{ 0.f, -1350.f, 3500.f, -100.f });

    return isBeginPlayEnd;
}

void Client::ClientWorld::Tick(_float deltaSeconds)
{
	static float elapsedTime = 0.f;
	elapsedTime += deltaSeconds;

	if (elapsedTime > 1.f)
	{
		std::cout << _pCoreManager->GetTimeManager()->GetFPS() << std::endl;
		elapsedTime = 0.f;
	}

	World::Tick(deltaSeconds);
}

void Client::ClientWorld::Render(ID2D1RenderTarget* pRenderTarget)
{
	World::Render(pRenderTarget);
	//test code

	/*pRenderTarget->SetTransform(Matx::Identity);
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
		D2D1::RectF(1300, 100, 1900, 200),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);

	bool NekoGrounded = _pNeko->GetComponent<::Core::MovementComponent>("MovementComponent")->IsGrounded();
	_bstring NekoGround = "Neko Grounded : ";
	if (NekoGrounded)
	{
		NekoGround += "True";
	}
	else
	{
		NekoGround += "False";
	}

	pRenderTarget->DrawTextW(
		NekoGround,
		NekoGround.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(1300, 300, 1900, 800),
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

	_bstring _explanation1 = 
		"[ Left & Right : 이동 | 적 방향 방향키 2번 : 달리기 | 적 반대방향 방향키 2번 : 백대쉬 | 공중 방향키 2번 : 공중 백대쉬 & 공중 대쉬 ]\n\n[ UP : 점프 | A : 약발 | S : 강발 ]\n\n[ A 연타 : 어시스턴트 모드 ]";

	pRenderTarget->DrawTextW(
		_explanation1,
		_explanation1.length(),
		_pCoreManager->GetFont(L"DemoFont"),
		D2D1::RectF(100, 1000, 1500, 1100),
		_pCoreManager->GetGraphicsPackage()->_pBrush
	);*/

	//test code end
}


