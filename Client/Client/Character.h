#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class AnimationComponent;
	class InputComponent;
}

struct InputEvent;

namespace Client
{
	class Character : public Core::Actor
	{
	private:
		enum StateFlag
		{
			STATE_IDLE = 1 << 1,
			STATE_MOVE = 1 << 2,
			STATE_DUCK = 1 << 3,
			STATE_ATTACK = 1 << 4,
			STATE_UP_ATTACK = 1 << 5,
			STATE_DIR_ATTACK = 1 << 6,
			STATE_JUMP = 1 << 7,
			STATE_JUMPING = 1 << 8
		};
	protected:
		explicit Character() = default;
		virtual ~Character() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

		void Attack(const InputEvent& inputEvent);
		void Move(const InputEvent& inputEvent);
		void Duck(const InputEvent& inputEvent);
		void JumpHandle(const InputEvent& inputEvent);
		void Jump(_float deltaSeconds);

	public:
		static Character* Create() { return new Character; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent* _pInputComponent{ nullptr };

	private:
		_uint _stateFlag{ 0 };
		Mathf::Vector2 _direction{ UnitVector::Zero };
		Mathf::Vector2 _velocity{ 200.f, 0.f };
		Mathf::Vector2 _gravity{ 0.f , 98.f };
		float _elapsedTime{ 0.f };
	};
}