#include "TestActor.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/InputComponent.h"
#include "../../Engine/Headers/BitmapComponent.h"
#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/Texture.h"
//#include "../../Engine/Headers/KhalaSystem.h"

void Client::TestActor::BeginPlay()
{
	Actor::BeginPlay();

	//__Khala->DefineNerveCord("Move", [&](__KhalaArgs args)
	//	{
	//		float x = __KhalaCast<float>(args[0]); //any_cast를 사용하여 인자를 캐스팅 -> 인자를 0번 인덱스부터 등록
	//		float y = __KhalaCast<float>(args[1]);

	//		Move(x, y);

	//		return true;
	//	});

	//__Khala->DefineNerveCord("IsMove", [&](__KhalaArgs args)
	//	{
	//		return _isMove;
	//	});

	_pInputComponent = AddComponent<::Core::InputComponent>("InputComponent");
	_pBitmapComponent = AddComponent<::Core::BitmapComponent>("BitmapComponent");

	_pInputComponent->BindInputEvent(DIP_RX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Rotate(inputEvent.value);
		});

	_pInputComponent->BindInputEvent(DIP_RT, InputType::TRIGGER, [&](const InputEvent& inputEvent)
		{
			_pInputComponent->SetVibration(0, inputEvent.value);

			Fire();
		});

	_pInputComponent->BindInputEvent(DIP_LX, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(inputEvent.value, 0);
		});

	_pInputComponent->BindInputEvent(DIP_LY, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			Move(0, inputEvent.value);
		});

	_pInputComponent->BindInputEvent(DIK_AXIS, InputType::AXIS, [&](const InputEvent& inputEvent)
		{
			//Move((float)inputEvent.x, (float)inputEvent.y);
			//__Khala->ConnectNerveCord("Move", { (float)inputEvent.x, (float)inputEvent.y });
			//__Khala->ConnectNerveCord("OuterMove", 
			//	{ (::Core::Actor*)this, (float)inputEvent.x, (float)inputEvent.y });
			
			if(inputEvent.x > 0)
				_isMove = true;
			//이런식으로 인풋 이벤트와 연동해서 이벤트를 발생시킬 수 있음
			//다만 인풋 이벤트와 별개의 이벤트를 생성후 실행하기도 하고, 바인드 함수 자체가 람다를
			//사용하기 때문에, 외부 함수에 접근이 가능해서, 불필요한 구현임.
		});

	_pInputComponent->AttachToInputManager();

	_pBitmapComponent->SetTextures(&_vecTextures);

}

void Client::TestActor::Tick(_float deltaTime)
{
	//std::cout << _pRootComponent->GetWorldLocation().x << " " 
	//	<< _pRootComponent->GetWorldLocation().y << std::endl;

	//__Khala->ConnectNerveCord("Fire", {}); //이벤트 설계자가 원하는 위치에 이벤트를 발생하는 함수

	Actor::Tick(deltaTime);

	_isMove = false;
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::EndPlay()
{
}
//test code
void Client::TestActor::Fire()
{
	//std::cout << "Fire" << std::endl;
}

void Client::TestActor::Rotate(float degree)
{
	_pRootComponent->AddRelativeRotation(degree);
}

void Client::TestActor::Move(float x, float y)
{
	_pRootComponent->AddRelativeLocation(Mathf::Vector2{x, y});
}
//test code end
