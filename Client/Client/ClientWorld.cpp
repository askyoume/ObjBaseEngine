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
#include "PlayerTwoFace.h"
#include "Timer.h"
#include "Mouse.h"

bool Client::ClientWorld::BeginPlay()
{
	//test code
	_pCoreManager->LoadFont(L"DemoFont", L"Client/Resources/Font/EFKratos.ttf", 16.f);
	_pCoreManager->LoadFont(L"NameFont", L"Client/Resources/Font/EFKratos.ttf", 12.f);
	//플레이어가 케릭터를 선택하면 그에 맞는 케릭터를 생성하도록 수정해야함
	//이걸 위해서 가장 편한방법은? 케릭터 클래스의 정보를 Asset파일(json기반)로 저장하고, 그 정보를 읽어와서 생성하는 방법이 있음.
	//그런데... 시간이 되겠어? ㅋㅋㅋ 이제 시간이 없어. 그냥 빠르게 만들어야지.
	SpawnActor(LAYER::FRONTOBJECT, "Aoko", Aoko::Create(), Mathf::Vector2{ 2350.f, -130.f });
	SpawnActor(LAYER::FRONTOBJECT, "Neko", Neko::Create(), Mathf::Vector2{ 3000.f, -130.f });
	//UI
	SpawnActor(LAYER::UI, "TestActor",		TestActor::Create(),	 Mathf::Vector2{ 967.5f, 1040.f });
	SpawnActor(LAYER::UI, "Timer",			Timer::Create(),		 Mathf::Vector2{ 967.5f, 60.f   });
	SpawnActor(LAYER::UI, "PlayerOneHP",	PlayerHP::Create(),		 Mathf::Vector2{ 525.f, 100.f   });
	SpawnActor(LAYER::UI, "PlayerTwoHP",	PlayerHP::Create(),		 Mathf::Vector2{ 1410.f, 100.f	});
	SpawnActor(LAYER::UI, "PlayerOneFace",	PlayerOneFace::Create(), Mathf::Vector2{ 336.f, 110.f   });
	SpawnActor(LAYER::UI, "PlayerTwoFace",	PlayerTwoFace::Create(), Mathf::Vector2{ 1599.f, 110.f  });
	SpawnActor(LAYER::UI, "Mouse",			Mouse::Create(),		 Mathf::Vector2{ 0.f, 0.f		});
	//배경도 그래야 함.
	SpawnActor(LAYER::BACKGROUND, "BackGround", BackGround::Create(), Mathf::Vector2{ 2750.f, -390.f });

	_pActorOne = FindActor("Aoko");
	_pActorTwo = FindActor("Neko");
	_pPlayerOneHP = dynamic_cast<PlayerHP*>(FindActor("PlayerOneHP"));
	_pPlayerTwoHP = dynamic_cast<PlayerHP*>(FindActor("PlayerTwoHP"));
	_pPlayerOneHP->SetPlayerInfo(_pActorOne);
	_pPlayerTwoHP->SetPlayerInfo(_pActorTwo);
	_pPlayerTwoHP->SwitchPlayer(PlayerID_Two);

	SettingCamera(PlayCameraActor::Create());
	SettingCameraPosition(Mathf::Vector2{ 1835.f, -530.f });
	SettingCameraOffset(Mathf::Vector2{0.f, -70.f});
	SetWorldSize(Mathf::Rect{ 0.f, -1350.f, 3500.f, -100.f });
	SetSortGreater(true);

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
}


