#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class AnimationComponent;
}

namespace Client
{
	class BackGround : public Core::Actor
	{
	protected:
		explicit BackGround() = default;
		virtual ~BackGround() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static BackGround* Create() { return new BackGround; }

	private:
		::Core::AnimationComponent* _pAnimationComponent{ nullptr };

	};
}