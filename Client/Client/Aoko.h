#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"
#include "../../Engine/Headers/Mathf.h"

#include "IPlayerInfo.h"

namespace Core
{
	class AnimationComponent;
	class InputComponent;
	class StateComponent;
	class MovementComponent;
	class BoxComponent;
	class CollisionComponent;
	class TextRenderComponent;
}

struct InputEvent;

namespace Client
{
	class Aoko final : public Core::Actor, public IPlayerInfo
	{
	protected:
		explicit Aoko() = default;
		virtual ~Aoko() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;

		void ExecuteMatchedCommands(_float deltaSeconds);

		void AutoComboHandler(const InputEvent& inputEvent);
		void LowKickHandler(const InputEvent& inputEvent);
		void MiddleKickHandler(const InputEvent& inputEvent);
		void Jump(const InputEvent& inputEvent);
		void Ducking(const InputEvent& inputEvent);
		void RightMoveHandler(const InputEvent& inputEvent);
		void LeftMoveHandler(const InputEvent& inputEvent);
		void StandHandler(const InputEvent& inputEvent);
		void Dead();

		// IPlayerInfo
		void DamageInvoker(int damage) override;
		int GetHP() const override;
		int GetMaxHP() const override;
		int GetGauge() const override;
		int GetMaxGauge() const override;

		void SetPlayClip(_pstring clipName);

	public:
		static Aoko* Create() { return new Aoko; }

	private:
		::Core::BoxComponent*        _pBodyBoxComponent{ nullptr };
		::Core::BoxComponent*        _pFootBoxComponent{ nullptr };
		::Core::MovementComponent*   _pMovementComponent{ nullptr };
		::Core::AnimationComponent*  _pAnimationComponent{ nullptr };
		::Core::InputComponent*		 _pInputComponent{ nullptr };
		::Core::StateComponent*		 _pStateComponent{ nullptr };
		::Core::TextRenderComponent* _pTextRenderComponent{ nullptr };

	private:
		bool _isComboStart{ false };
		int _currentHP{ 8000 };
		int _maxHP{ 10000 };
		int _currentGauge{ 0 };
		int _maxGauge{ 0 };
	};
}