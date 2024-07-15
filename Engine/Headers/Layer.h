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
		using CollisionQueue = std::vector<CollisionComponent*>;

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
		void AddCollisionQueue(CollisionComponent* pCollisionComponent);
		void RemoveCollisionQueue(CollisionComponent* pCollisionComponent);

	public:
		static Layer* Begin();
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		void Remove() override;

	private:
		Actors _actors;
		CollisionQueue _collisionQueue;
		RenderQueue _renderQueue;
		CameraActor* _pCameraActor{ nullptr };
	};
}