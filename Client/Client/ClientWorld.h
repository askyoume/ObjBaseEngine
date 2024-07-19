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
	class ClientWorld final : public Core::World
	{
	private:
		explicit ClientWorld() = default;
		virtual ~ClientWorld() = default;

	public:
		bool BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Render(ID2D1RenderTarget* pRenderTarget) override;

	public:
		static ClientWorld* Create() { return new ClientWorld; }

	private:
		::Core::Actor* _pActorOne{ nullptr };
		::Core::Actor* _pActorTwo{ nullptr };
		Aoko* _pAoko{ nullptr };
		Neko* _pNeko{ nullptr };
	};
}