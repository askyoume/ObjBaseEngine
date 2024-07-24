#pragma once

#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class InputComponent;
	class BitmapComponent;
}

namespace Client
{
	class TestActor : public Core::Actor
	{
	protected:
		explicit TestActor() = default;
		virtual ~TestActor() = default;
	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;


	public:
		static TestActor* Create() { return new TestActor; }

	private:
		::Core::InputComponent* _pInputComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
	};
}