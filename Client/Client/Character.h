#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class AnimationComponent;
	class InputComponent;
}

namespace Client
{
	class Charactor : public Core::Actor
	{
	private:
		enum State
		{
			IDLE = 0,
			MOVE,
			DUCK,
			ATTACK
		};

		enum StateFlag
		{
			STATE_IDLE = 1 << 1,
			STATE_MOVE = 1 << 2,
			STATE_DUCK = 1 << 3,
			STATE_ATTACK = 1 << 4
		};
	protected:
		explicit Charactor() DEFAULT;
		virtual ~Charactor() DEFAULT;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static Charactor* Create() { return new Charactor; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent* _pInputComponent{ nullptr };
		_uint _stateFlag{ 0 };
		bool _isMove{ false };
	};
}