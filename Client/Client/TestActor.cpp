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
	//		float x = __KhalaCast<float>(args[0]); //any_cast�� ����Ͽ� ���ڸ� ĳ���� -> ���ڸ� 0�� �ε������� ���
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
			//�̷������� ��ǲ �̺�Ʈ�� �����ؼ� �̺�Ʈ�� �߻���ų �� ����
			//�ٸ� ��ǲ �̺�Ʈ�� ������ �̺�Ʈ�� ������ �����ϱ⵵ �ϰ�, ���ε� �Լ� ��ü�� ���ٸ�
			//����ϱ� ������, �ܺ� �Լ��� ������ �����ؼ�, ���ʿ��� ������.
		});

	_pInputComponent->AttachToInputManager();

	_pBitmapComponent->SetTextures(&_vecTextures);

}

void Client::TestActor::Tick(_float deltaTime)
{
	//std::cout << _pRootComponent->GetWorldLocation().x << " " 
	//	<< _pRootComponent->GetWorldLocation().y << std::endl;

	//__Khala->ConnectNerveCord("Fire", {}); //�̺�Ʈ �����ڰ� ���ϴ� ��ġ�� �̺�Ʈ�� �߻��ϴ� �Լ�

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
