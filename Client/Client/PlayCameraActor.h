#pragma once
#include "../../Engine/Headers/CameraActor.h"

namespace Core
{
	class Actor;
}

namespace Client
{
	class PlayCameraActor : public Core::CameraActor
	{
	protected:
		explicit PlayCameraActor() = default;
		virtual ~PlayCameraActor() = default;

	public:
		virtual void BeginPlay() override;
		virtual void Tick(_float deltaTime) override;

	public:
		static PlayCameraActor* Create();

	private:
		::Core::Actor* _pActorOne{ nullptr };
		::Core::Actor* _pActorTwo{ nullptr };
	};
}