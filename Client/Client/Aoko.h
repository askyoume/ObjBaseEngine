#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

namespace Core
{
	class AnimationComponent;
	class InputComponent;
	class StateComponent;
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

		void Attack(const InputEvent& inputEvent);
		void Move(const InputEvent& inputEvent);
		void Dead();

		Mathf::Vector2 GetDirection() const { return _direction; }
		Mathf::Vector2 GetVelocity() const { return _velocity; }

		void SetPlayClip(_pstring clipName);

	public:
		static Aoko* Create() { return new Aoko; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::InputComponent*		_pInputComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };

	private:
		_uint _stateFlag{ 0 };
		Mathf::Vector2 _direction{ UnitVector::Zero };
		Mathf::Vector2 _velocity{ 200.f, 0.f };
		Mathf::Vector2 _gravity{ 0.f , 98.f };
		float _elapsedTime{ 0.f };
	};
}