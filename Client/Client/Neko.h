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
	class TextRenderComponent;
}

struct InputEvent;

namespace Client
{
	class Neko final : public Core::Actor, public IPlayerInfo
	{
	protected:
		explicit Neko() = default;
		virtual ~Neko() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void ReviveInitialize() override;

		// IPlayerInfo
		void DamageInvoker(int damage) override;
		int GetHP() const override;
		int GetMaxHP() const override;
		int GetGauge() const override;
		int GetMaxGauge() const override;

	public:
		static Neko* Create();

	private:
		::Core::BoxComponent*		_pBoxComponent{ nullptr };
		::Core::InputComponent*		_pInputComponent{ nullptr };
		::Core::MovementComponent*  _pMovementComponent{ nullptr };
		::Core::AnimationComponent* _pTargetAnimationComponent{ nullptr };
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };
		::Core::StateComponent*		_pAIComponent{ nullptr };
		::Core::StateComponent*		_pStateComponent{ nullptr };
		::Core::StateComponent*		_pTargetStateComponent{ nullptr };
		::Core::TextRenderComponent* _pTextRenderComponent{ nullptr };

	private:
		int _currentHP{ 10000 };
		int _maxHP{ 10000 };
		int _currentGauge{ 0 };
		int _maxGauge{ 0 };

	private:
		float _elapsedTime{ 0.f };
		bool _isFrameEnd{ false };
		bool _isDead{ false };
	};
}