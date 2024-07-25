#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class Layer : public Core
	{
	private:
		using ActorsList = std::list<Actor*>;
		using RenderQueue = std::vector<RenderComponent*>;

	private:
		Layer() = default;
		~Layer() = default;

	public:
		void Tick(_float deltaSeconds);
		void Fixed();
		void Render(ID2D1RenderTarget* pRenderTarget);
		void EndPlay();

	public:
		bool InsertActor(Actor* pActor);
		bool AddActor(Actor* pActor);
		Actor* GetActor(_pstring name);
		bool DestroyActor();
		void AddRenderQueue(RenderComponent* pRenderComponent);
		void RemoveRenderQueue(RenderComponent* pRenderComponent);

	public:
		static Layer* Begin(int index);
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		void Remove() override;

	private:
		ActorsList	 _actors;
		RenderQueue	 _renderQueue;
		CameraActor* _pCameraActor{ nullptr };
		int		 _layerIndex{ 0 };
	};
}