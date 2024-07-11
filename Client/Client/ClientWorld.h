#pragma once
#include "../../ObjectBaseEngine/Client_Macro.h"
#include "../../Engine/Headers/World.h"

namespace Core
{
	class CoreManager;
}

namespace Client
{
	class Aoko;
	class ClientWorld final : public Core::World
	{
	private:
		explicit ClientWorld() DEFAULT;
		virtual ~ClientWorld() DEFAULT;

	public:
		bool BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Render(ID2D1RenderTarget* pRenderTarget) override;

	public:
		static ClientWorld* Create() { return new ClientWorld; }

	private:
		Aoko* _pAoko{ nullptr };
	};
}