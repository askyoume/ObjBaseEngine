#pragma once
#include "../../Engine/Headers/CameraActor.h"

namespace Core
{
	class Actor;
	class AnimationComponent;
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
		void PlayerLocationClamp();

	private:
		::Core::Actor* _pActorOne{ nullptr };
		::Core::Actor* _pActorTwo{ nullptr };
		::Core::AnimationComponent* _pActorOneAnimationComponent{ nullptr };
		::Core::AnimationComponent* _pActorTwoAnimationComponent{ nullptr };

	private:
		Mathf::Vector2 _playerOneLocation{ };
		Mathf::Vector2 _playerTwoLocation{ };

	private:
		float _width	  { 0.f };
		float _height	  { 0.f };
		float _halfWidth  { 0.f };
		float _halfHeight { 0.f };

	private:
		bool  _isOneClamp{ false };
		bool  _isTwoClamp{ false };
	};
}