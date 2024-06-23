#pragma once
#include "Actor.h"

namespace Core
{
	CORECLASS()
	class CameraActor : public Actor
	{
	public:
		enum MoveDirectionFlag
		{
			Up = 1 << 0,
			Down = 1 << 1,
			Left = 1 << 2,
			Right = 1 << 3,
		};
	protected:
		explicit CameraActor() DEFAULT;
		virtual ~CameraActor() DEFAULT;
	public:
		//Actor
		virtual void BeginPlay() override {};
		virtual void Tick(_float deltaTime) override;
		virtual CameraComponent* GetCameraComponent() { return _cameraComponent; }

		void TrackTarget(Actor* pTarget);
		void SetCameraLerpFactor(float lerpFactor) { _cameraLerpFactor = lerpFactor; }
		void SettingTracking(bool isTracking) { _isTracking = isTracking; }
		bool IsTracking() const { return _isTracking; }
		bool IsMove() const { return _isMove; }

	protected:
		virtual bool Initialize();

	public:
		static CameraActor* Create();

	private:
		CameraComponent*	_cameraComponent{ nullptr };
		Mathf::Vector2		_oldLocation{};
		float				_cameraLerpFactor{ 3.5f };
		_uint				_moveDirectionFlag{};
		bool				_isTracking{ false };
		bool				_isMove{ false };
	};
}