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
}

struct InputEvent;

namespace Client
{
	class Aoko : public Core::Actor
	{
	protected:
		explicit Aoko() DEFAULT;
		virtual ~Aoko() DEFAULT;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

		void MatchCombo();
		InputEvent GetPrevInputEvent();

		void Attack(const InputEvent& inputEvent);
		void Move(const InputEvent& inputEvent);
		void MoveHandler(const InputEvent& inputEvent);
		void Dead();

		void SetPlayClip(_pstring clipName);

	public:
		static Aoko* Create() { return new Aoko; }

	private:
		::Core::MovementComponent*  _pMovementComponent{ nullptr };
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent*		_pInputComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };
		std::deque<InputEvent>		_inputQueue;
	};
}