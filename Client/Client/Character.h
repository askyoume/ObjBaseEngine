#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

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

		void Jump(_float deltaTime);
		void Attack(const InputEvent& inputEvent);

	public:
		static Charactor* Create() { return new Charactor; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent* _pInputComponent{ nullptr };

	private:
		_uint _stateFlag{ 0 };
		float _directionX{ 1.f };
		float _directionY{ 1.f };
		float _jumpPower{ 300.f };
		float _gravity{ 0.f };
		float _jumpTime{ 0.f };
		float _jumpMaxTime{ 0.5f };
	};
}