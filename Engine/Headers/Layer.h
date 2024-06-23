#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class Layer : public Core
	{
	private:
		using Actors = std::list<Actor*>;
		using RenderQueue = std::vector<RenderComponent*>;

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
		void AddRenderQueue(RenderComponent* pRenderComponent);
		void RemoveRenderQueue(RenderComponent* pRenderComponent);

	public:
		static Layer* Begin();
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		void Remove() override;

	private:
		Actors _actors;
		RenderQueue _renderQueue;
		ID2D1Layer* _pLayer{ nullptr };
		CameraActor* _pCameraActor{ nullptr };
	};
}