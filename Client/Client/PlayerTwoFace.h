#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class BitmapComponent;
}

namespace Client
{
	class PlayerTwoFace final : public Core::Actor
	{
	protected:
		explicit PlayerTwoFace() = default;
		virtual ~PlayerTwoFace() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static PlayerTwoFace* Create() { return new PlayerTwoFace; }

	private:
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent2{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent3{ nullptr };
	};
}