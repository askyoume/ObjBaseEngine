#pragma once
#include "Core_Define.h"
#include "SceneComponent.h"
#include "RenderComponent.h"

namespace Core
{
	class CollisionComponent abstract : public RenderComponent //temperaly inherit RenderComponent for debug draw
	{
	public:
		using Collider = Collider::ColliderType;
		using Collision = Collision::CollisionType;
		using CollisionState = std::set<CollisionComponent*>;
		using IgnoreLayerList = std::set<int>;

	protected:
		explicit CollisionComponent() = default;
		virtual ~CollisionComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override PURE;
		virtual bool IsCollision(CollisionComponent* pOther) PURE;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override PURE; //for debug draw
	
	public:
		void ProcessCollision();
		void ProcessCollision(CollisionComponent* pOtherComponent);

		void AddCollisionState(CollisionComponent* pOtherComponent);
		void ClearCollisionState();
		void UpdateCollisionState();

	public:
		void SetColliderType(Collider colliderType) { _collider = colliderType; }
		Collider GetColliderType() const { return _collider; }

		void SetCollisionType(Collision collisionType) { _type = collisionType; }
		Collision GetCollisionType() const { return _type; }

		void SetIgnoreLayer(int layerIndex) { _ignoreLayerList.insert(layerIndex); }
		void RemoveIgnoreLayer(int layerIndex) { _ignoreLayerList.erase(layerIndex); }
		const IgnoreLayerList& GetIgnoreLayerList() const { return _ignoreLayerList; }

	public:
		bool operator==(_pstring _name) const { return !strcmp(name, _name); }
		bool operator!=(_pstring _name) const { return strcmp(name, _name); }

	public:
		void AddColliderInLayer();

	public:
		void BeginPlay() override{};
		void EndPlay() override{};

	protected:
		Collider		_collider{ Collider::COLLIDER_NONE };
		Collision		_type{ Collision::COLLISION_IGNORE };
		IgnoreLayerList _ignoreLayerList;
		CollisionState	_previousCollisionState;
		CollisionState	_currentCollisionState;
	};
}
