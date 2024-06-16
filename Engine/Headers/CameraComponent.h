#pragma once
#include "SceneComponent.h"

namespace Core
{
	CORECLASS()
	class CameraComponent : public SceneComponent, public Transform
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
		void UpdateTransform() override;
		void UpdateVelocity() override;

	protected:
		virtual bool Initialize() { return true; }
		virtual void Remove() {};

	public:
		static CameraComponent* Create() { return new CameraComponent; }

	};
}