#pragma once
#include "Core_Define.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class World : public Core
	{
	private:
		using Layers = std::vector<Layer*>;
		using ActorMap = std::unordered_map<_pstring, Actor*>;

	protected:
		explicit World() DEFAULT;
		virtual	~World() DEFAULT;
	
	public:
		bool InitializeWorld(int layerSize);
		void Remove() override;

	public:
		virtual bool BeginPlay() PURE;
		virtual void Tick(_float deltaTime);
		virtual void Fixed();
		virtual void Render(ID2D1RenderTarget* pRenderTarget);
		virtual void EndPlay();

	public:
		bool InitializeLayer(int layerSize);
		Layer* GetLayer(int layerIndex) const;
		ActorMap& GetActorMap() { return _actorMap; }
		void AddLayer(int layerIndex, Layer* pLayer);
		void RemoveLayer(int layerIndex);
		void ClearLayer();
		int GetLayerSize() const { return _layerSize;}
		void SettingTrackingCameraTarget(Actor* pTargetActor);

	public:
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location);
		bool RemoveActor(_pstring name);
		Actor* FindActor(_pstring name);

	protected:
		CoreManager* _pCoreManager{ nullptr };
		CameraActor* _pCameraActor{ nullptr };

	private:
		ActorMap _actorMap;
		Layers _vecLayers;
		int _layerSize{ 0 };
	};
}