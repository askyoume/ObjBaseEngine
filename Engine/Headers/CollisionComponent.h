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

	protected:
		explicit CollisionComponent() = default;
		virtual ~CollisionComponent() = default;

	public:
		virtual void TickComponent(_float deltaTime) override PURE;
		virtual bool IsCollision(CollisionComponent* pOther) PURE;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override PURE; //for debug draw
	
	public:
		void ProcessCollision();
		void ProcessCollision(Actor* pOther);

	public:
		void SetColliderType(Collider colliderType) { _collider = colliderType; }
		Collider GetColliderType() const { return _collider; }

		void SetCollisionType(Collision collisionType) { _type = collisionType; }
		Collision GetCollisionType() const { return _type; }

	public:
		void AddColliderInLayer();

	public:
		void BeginPlay() override{};
		void EndPlay() override{};

	protected:
		Collider  _collider{ Collider::COLLIDER_NONE };
		Collision _type{ Collision::COLLISION_IGNORE };

	protected:
		CollisionState _previousCollisionState;
		CollisionState _currentCollisionState;
	};
}