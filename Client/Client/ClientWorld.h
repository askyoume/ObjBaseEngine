#pragma once
#include "../../Engine/Headers/Client_Macro.h"
#include "../../Engine/Headers/World.h"

namespace Core
{
	class CoreManager;
	class Actor;
}

namespace Client
{
	class Aoko;
	class Neko;
	class PlayerHP;
	class ClientWorld final : public Core::World
	{
	private:
		explicit ClientWorld() = default;
		virtual ~ClientWorld() = default;

	public:
		bool BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Render(ID2D1RenderTarget* pRenderTarget) override;
		//void CustomRenderSort() override;

	public:
		static ClientWorld* Create() { return new ClientWorld; }

	private:
		::Core::Actor* _pActorOne{ nullptr };
		::Core::Actor* _pActorTwo{ nullptr };
		PlayerHP* _pPlayerOneHP{ nullptr };
		PlayerHP* _pPlayerTwoHP{ nullptr };
	};
}