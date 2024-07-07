#pragma once
#include "SceneComponent.h"
#include "ACollision.h"

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
		Mathf::Vector2 GetCenterPosition() const { return _centerPosition; }

		void SetCameraSize(Mathf::Vector2 cameraSize) { _cameraSize = cameraSize; }
		Mathf::Vector2 GetCameraSize() const { return _cameraSize; }

		void SetCameraOffset(Mathf::Vector2 cameraOffset) { _cameraOffset = cameraOffset; }
		Mathf::Vector2 GetCameraOffset() const { return _cameraOffset; }

		void SetCameraZoomScale(Mathf::Vector2 cameraZoomScale) { _cameraZoomScale = cameraZoomScale; }
		Mathf::Vector2 GetCameraZoomScale() const { return _cameraZoomScale; }

		bool CheckCollision(ACollision* pCollision);

	protected:
		virtual bool Initialize();
		virtual void Remove();

	public:
		static CameraComponent* Create();

	private:
		Mathf::Matrix3x2 _cameraMatrix{ Matx::Identity };
		Mathf::Vector2   _cameraZoomScale{ 1.f, 1.f };
		Mathf::Vector2   _centerPosition{ 0.f, 0.f };
		Mathf::Vector2   _cameraSize{ 0.f, 0.f };
		Mathf::Vector2   _cameraOffset{ 0.f, 0.f };
		ACollision*		 _pCollision{ nullptr };
	};
}