#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class BitmapComponent;
	class BoxComponent;
	class CollisionComponent;
}

namespace Client
{
	class Timer final : public Core::Actor
	{
	private:
		enum TimerNumberTexture
		{
			TimerNumberTexture_Infinity = 1,
			TimerNumberTexture_0,
			TimerNumberTexture_1,
			TimerNumberTexture_2,
			TimerNumberTexture_3,
			TimerNumberTexture_4,
			TimerNumberTexture_5,
			TimerNumberTexture_6,
			TimerNumberTexture_7,
			TimerNumberTexture_8,
			TimerNumberTexture_9,
			TimerNumberTexture_Max,
		};
	protected:
		explicit Timer() = default;
		virtual ~Timer() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		void NotifyActorBlock(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorBeginOverlap(::Core::CollisionComponent* pOtherComponent) override;
		void NotifyActorEndOverlap(::Core::CollisionComponent* pOtherComponent) override;

	public:
		void SetTimerOn(bool isOn) { _isTimerOn = isOn; }
		bool GetTimerOn() const { return _isTimerOn; }
		void SetTimeOver(bool isOver) { _isTimeOver = isOver; }
		bool GetTimeOver() const { return _isTimeOver; }
		void ResetTimer() { _remainTime = _roundTime; }

	public:
		static Timer* Create() { return new Timer; }

	private:
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent2{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent3{ nullptr };
		::Core::BoxComponent*	 _pBoxComponent{ nullptr };

	private:
		Mathf::Vector2 _infinityPos{ 0.f, 0.f };

	private:
		const float _roundTime{ 60.f };
		float		_remainTime{ 60.f };
		float		_elapsedTime{ 0.f };
		bool        _isTimeOver{ false };
		bool		_isTimerOn{ true };
	};
}