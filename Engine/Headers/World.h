#pragma once
#include "Core_Define.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class World abstract : public Core
	{
	private:
		using Layers = std::vector<Layer*>;
		using ActorMap = std::unordered_map<_pstring, Actor*>;

	protected:
		explicit World() = default;
		virtual	~World() = default;
	
	public:
		bool InitializeWorld(int layerSize);
		bool BeginPlayEnd();
		ReadOnly_Property(bool, isBeginPlayEnd);
		_Get(isBeginPlayEnd)
		{
			return World::BeginPlayEnd();
		}
		void Remove() override;

	public:
		virtual bool BeginPlay() PURE;
		virtual void Tick(_float deltaSeconds);
		virtual void Fixed();
		virtual void Render(ID2D1RenderTarget* pRenderTarget);
		virtual void EndPlay();

	public:
		//Layer
		bool InitializeLayer(int layerSize);
		Layer* GetLayer(int layerIndex) const;
		void AddLayer(int layerIndex, Layer* pLayer);
		void RemoveLayer(int layerIndex);
		void ClearLayer();
		int GetLayerSize() const { return _layerSize; }

	public:
		//RenderSort
		virtual void CustomRenderSort() {};
		void SetCustomRenderSort(bool isCustomRenderSort) { _isCustomRenderSort = isCustomRenderSort; }
		void SetSortGreater(bool isSortGreater) { _isSortGreater = isSortGreater; }
		bool IsCustomRenderSort() const { return _isCustomRenderSort; }
		bool IsSortGreater() const { return _isSortGreater; }

	public:
		//Camera
		CameraActor* GetCameraActor() { return _pCameraActor; }
		void SettingCamera(CameraActor* pCameraActor = nullptr);
		void SettingCameraPosition(Mathf::Vector2 position);
		void SettingTrackingCameraTarget(Actor* pTargetActor);
		void SetCameraLerpFactor(float lerpFactor);
		void SettingTrackingCamera(bool isTracking);
		bool IsTrackingCamera() const;
		void SettingCameraOffset(Mathf::Vector2 offset);

	public:
		//WorldSize
		void SetWorldSize(Mathf::Rect worldSize) { _worldSize = worldSize; }
		Mathf::Rect GetWorldSize() const { return _worldSize; }

	public:
		//Actor
		ActorMap& GetActorMap() { return _actorMap; }
		Actor* FindActor(_pstring name);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location);
		bool RemoveActor(_pstring name);
		bool ReviveActor(_pstring name);

	protected:
		CoreManager* _pCoreManager{ nullptr };
		CameraActor* _pCameraActor{ nullptr };
		Canvas*		 _pCanvas{ nullptr };

	protected:
		ActorMap			_actorMap;
		Layers				_vecLayers;

	protected:
		Mathf::Matrix3x2	_worldTransform{ Matx::Identity };
		Mathf::Vector2		_worldCenter{ UnitVector::Zero };
		Mathf::Rect			_worldSize{};

	protected:
		int					_layerSize{};
		bool				_isCustomRenderSort{ false };
		bool				_isSortGreater{ false };
	};
}