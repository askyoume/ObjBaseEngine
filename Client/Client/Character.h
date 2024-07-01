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
	class Charactor : public Core::Actor
	{
	private:
		enum StateFlag
		{
			STATE_IDLE = 1 << 1,
			STATE_MOVE = 1 << 2,
			STATE_DUCK = 1 << 3,
			STATE_ATTACK = 1 << 4,
			STATE_JUMP = 1 << 5,
			STATE_JUMPING = 1 << 6
		};
	protected:
		explicit Charactor() DEFAULT;
		virtual ~Charactor() DEFAULT;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

		void Attack(const InputEvent& inputEvent);
		void Move(const InputEvent& inputEvent);
		void Duck(const InputEvent& inputEvent);
		void JumpHandle(const InputEvent& inputEvent);
		void Jump(_float deltaTime);

	public:
		static Charactor* Create() { return new Charactor; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent* _pInputComponent{ nullptr };

	private:
		_uint _stateFlag{ 0 };
		Mathf::Vector2 _direction{ UnitVector::One };
		Mathf::Vector2 _velocity{ 200.f, -200.f };
		Mathf::Vector2 _gravity{ 0.f , 98.f };
		float _elapsedTime{ 0.f };
	};
}