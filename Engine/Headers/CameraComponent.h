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

	protected:
		virtual bool Initialize() { return true; }
		virtual void Remove() {};

	public:
		static CameraComponent* Create() { return new CameraComponent; }

	private:
		Mathf::Matrix3x2 _cameraMatrix{ Matx::Identity };
	};
}