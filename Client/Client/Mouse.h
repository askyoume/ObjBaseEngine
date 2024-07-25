#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class InputComponent;
	class BoxComponent;
}

namespace Client
{
	class Mouse final : public Core::Actor
	{
	protected:
		explicit Mouse() = default;
		virtual ~Mouse() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;

		void OnMove(const InputEvent& inputEvent);
		void OnClick(const InputEvent& inputEvent);

	public:
		static Mouse* Create() { return new Mouse; }

	private:
		::Core::BoxComponent*	_pBoxComponent{ nullptr };
		::Core::InputComponent* _pInputComponent{ nullptr };

	private:
		POINT _mousePosition{ 0, 0 };
	};
}