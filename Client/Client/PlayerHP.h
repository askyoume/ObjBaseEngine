#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Core
{
	class BitmapComponent;
}

enum PlayerID : _uint
{
	PlayerID_One = 1,
	PlayerID_Two,
	PlayerID_Max,
};

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
		void SetPlayerInfo(::Core::Actor* pPlayerInfo);
		void SwitchPlayer(_uint playerID);

	public:
		static PlayerHP* Create() { return new PlayerHP; }

	private:
		::Core::BitmapComponent* _pBitmapComponent{ nullptr };
		::Core::BitmapComponent* _pBitmapComponent2{ nullptr };
		IPlayerInfo*			 _pPlayerInfo{ nullptr };

	private:
		Mathf::Rect _textureRect{ 0.f, 0.f, 0.f, 0.f };
		int _previousHP{ 0 };
		int _currentHP{ 0 };
		int _maxHP{ 0 };
		float _hpToPixel{ 0.f };
		float _currentHPFraction{ 0.f };
	};
}