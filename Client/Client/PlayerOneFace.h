#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class BitmapComponent;
}

namespace Client
{
	class PlayerOneFace final : public Core::Actor
	{
	protected:
		explicit PlayerOneFace() = default;
		virtual ~PlayerOneFace() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static PlayerOneFace* Create() { return new PlayerOneFace; }

	private:
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent2{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent3{ nullptr };
	};
}