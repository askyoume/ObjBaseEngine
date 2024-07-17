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
	class CollisionComponent;
}

struct InputEvent;

namespace Client
{
	class Aoko final : public Core::Actor
	{
	protected:
		explicit Aoko() = default;
		virtual ~Aoko() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;

		void MatchCombo(_float deltaTime);
		InputEvent GetPrevInputEvent();

		void Attack(const InputEvent& inputEvent);
		void Jump(const InputEvent& inputEvent);
		void Ducking(const InputEvent& inputEvent);
		void RightMoveHandler(const InputEvent& inputEvent);
		void LeftMoveHandler(const InputEvent& inputEvent);
		void StandHandler(const InputEvent& inputEvent);
		void Dead();

		void SetPlayClip(_pstring clipName);

	public:
		static Aoko* Create() { return new Aoko; }

	private:
		::Core::BoxComponent*       _pBodyBoxComponent{ nullptr };
		::Core::BoxComponent*       _pFootBoxComponent{ nullptr };
		::Core::MovementComponent*  _pMovementComponent{ nullptr };
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent*		_pInputComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };
		std::deque<InputEvent>		_inputQueue;

	private:
		float _comboTime{ 0.f };
	};
}