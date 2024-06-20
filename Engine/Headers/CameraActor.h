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

	protected:
		virtual bool Initialize();
		virtual void Remove() {};

	public:
		static CameraActor* Create();

	private:
		CameraComponent* _cameraComponent{ nullptr };
	};
}