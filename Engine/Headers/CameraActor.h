#pragma once
#include "CameraComponent.h"
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
		virtual CameraComponent* GetCameraComponent() { return _cameraComponent; }

	protected:
		virtual bool Initialize() { return true; }
		virtual void Remove() {};

	public:
		static CameraActor* Create() { return new CameraActor; }

	private:
		CameraComponent* _cameraComponent{ nullptr };
	};
}