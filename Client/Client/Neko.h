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
	class Neko : public Core::Actor
	{
	protected:
		explicit Neko() = default;
		virtual ~Neko() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static Neko* Create();

	private:
		::Core::MovementComponent*  _pMovementComponent{ nullptr };
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::StateComponent*		_pAIComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };
	};
}