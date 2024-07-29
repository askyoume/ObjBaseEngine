#pragma once

#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class InputComponent;
	class BoxComponent;
	class TextRenderComponent;
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
		virtual void NotifyActorBlock(::Core::CollisionPackage Components) override;
		virtual void NotifyActorBeginOverlap(::Core::CollisionPackage Components) override;
		virtual void NotifyActorEndOverlap(::Core::CollisionPackage Components) override;


	public:
		static TestActor* Create() { return new TestActor; }

	private:
		::Core::InputComponent*		 _pInputComponent{ nullptr };
		::Core::TextRenderComponent* _pTextRenderComponent{ nullptr };
		::Core::BitmapComponent*	 _pBitmapComponent{ nullptr };
		::Core::BoxComponent*		 _pBoxComponent{ nullptr };
		::Core::Actor*				 _pTargetActor{ nullptr };
	};
}