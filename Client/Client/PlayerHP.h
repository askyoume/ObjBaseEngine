#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class BitmapComponent;
}

namespace Client
{
	Interface IPlayerInfo;
	class PlayerHP final : public Core::Actor
	{
	protected:
		explicit PlayerHP() = default;
		virtual ~PlayerHP() = default;

	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static PlayerHP* Create() { return new PlayerHP; }

	private:
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent2{ nullptr };
		IPlayerInfo*			 _pPlayerInfo{ nullptr };

	private:
		int _currentHP{ 0 };
		int _maxHP{ 0 };
		float _maxHPUnit{ 0.f };
		float _currentHPPercent{ 0.f };
	};
}