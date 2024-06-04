#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class World : public Core
	{
	private:
		using Layers = std::vector<Layer*>;
	private:
		World() DEFAULT;
		~World() DEFAULT;
	
	public:
		static World* Begin();
		bool InitializeWorld(int layerSize);
		void Remove() override;

	public:
		void Tick(_float deltaTime);
		void Fixed();
		void Render(ID2D1RenderTarget* pRenderTarget);
		void EndPlay();

	public:
		bool InitializeLayer(int layerSize);
		void AddLayer(int layerIndex, Layer* pLayer);
		void RemoveLayer(int layerIndex);
		void ClearLayer();
		int GetLayerSize() const { return _layerSize;}

	public:
		bool AddActor(int layerIndex, Actor* pActor);
		Actor* FindActor(int layerIndex, _pstring name);

	private:
		Layers _vecLayers;
		int _layerSize{ 0 };
	};
}