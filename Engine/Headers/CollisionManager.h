#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class CollisionManager : public Core
	{
	public:
		using CollsionData = std::pair<int, CollisionComponent*>;
		using CollisionQueue = std::vector<CollsionData>;

	protected:
		explicit CollisionManager() = default;
		virtual ~CollisionManager() = default;

	public:
		void SimulateCollision();
		void AddCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent);
		void RemoveCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent);

	public:
		static CollisionManager* Create();
		void Remove();

	private:
		CollisionQueue _collisionQueue;
	};
}