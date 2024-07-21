#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class AnimationComponent;
	class InputComponent;
	class StateComponent;
	class MovementComponent;
	class BoxComponent;
}

struct InputEvent;

namespace Client
{
	class Neko final : public Core::Actor
	{
	protected:
		explicit Neko() = default;
		virtual ~Neko() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;

	public:
		static Neko* Create();

	private:
		::Core::BoxComponent*		_pBoxComponent{ nullptr };
		::Core::InputComponent*		_pInputComponent{ nullptr };
		::Core::MovementComponent*  _pMovementComponent{ nullptr };
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::StateComponent*		_pAIComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };
	};
}