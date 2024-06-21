#pragma once
#include "SceneComponent.h"

namespace Core
{
	CORECLASS()
	class CameraComponent : public SceneComponent
	{
	protected:
		explicit CameraComponent() DEFAULT;
		virtual ~CameraComponent() DEFAULT;
	public:
		//Component
		virtual void BeginPlay() override {};
		virtual void TickComponent(_float deltaTime) override;
		virtual void EndPlay() override {};

	public:
		void SetCenterPosition(Mathf::Vector2 centerPosition) { _centerPosition = centerPosition; }
		Mathf::Vector2 GetCenterPosition() { return _centerPosition; }

		void SetCameraSize(Mathf::Vector2 cameraSize) { _cameraSize = cameraSize; }
		Mathf::Vector2 GetCameraSize() { return _cameraSize; }

		void SetCameraOffset(Mathf::Vector2 cameraOffset) { _cameraOffset = cameraOffset; }
		Mathf::Vector2 GetCameraOffset() { return _cameraOffset; }

		void SetCameraZoomScale(Mathf::Vector2 cameraZoomScale) { _cameraZoomScale = cameraZoomScale; }
		Mathf::Vector2 GetCameraZoomScale() { return _cameraZoomScale; }

	protected:
		virtual bool Initialize() { return true; }
		virtual void Remove() {};

	public:
		static CameraComponent* Create() { return new CameraComponent; }

	private:
		Mathf::Matrix3x2 _cameraMatrix{ Matx::Identity };
		Mathf::Vector2   _cameraZoomScale{ 1.f, 1.f };
		Mathf::Vector2   _centerPosition{ 0.f, 0.f };
		Mathf::Vector2   _cameraSize{ 0.f, 0.f };
		Mathf::Vector2   _cameraOffset{ 0.f, 0.f };
	};
}