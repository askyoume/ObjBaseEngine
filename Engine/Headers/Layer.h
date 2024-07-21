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
		static Layer* Begin(_uint index);
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		void Remove() override;

	private:
		ActorsList	 _actors;
		RenderQueue	 _renderQueue;
		CameraActor* _pCameraActor{ nullptr };
		_uint		 _layerIndex{ 0 };
	};
}