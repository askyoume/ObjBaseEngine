#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class Layer : public Core
	{
	private:
		using Actors = std::list<Actor*>;
	private:
		Layer() DEFAULT;
		~Layer() DEFAULT;

	public:
		void Tick(_float deltaTime);
		void Fixed();
		void Render(ID2D1RenderTarget* pRenderTarget);
		void EndPlay();

	public:
		bool AddActor(Actor* pActor);
		Actor* GetActor(_pstring name);
		bool DestroyActor();

	public:
		static Layer* Begin();
		void Remove() override;

	private:
		Actors _actors;
	};
}