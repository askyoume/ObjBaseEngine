#pragma once
#include "Actor.h"

namespace Core
{
	CORECLASS()
	class CameraActor : public Actor
	{
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

	protected:
		virtual bool Initialize();
		virtual void Remove() {};

	public:
		static CameraActor* Create();

	private:
		CameraComponent* _cameraComponent{ nullptr };
		float _cameraLerpFactor{ 3.5f };
		bool _isTracking{ false };
	};
}