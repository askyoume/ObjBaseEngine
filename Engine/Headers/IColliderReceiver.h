#pragma once
#include "Core_Define.h"
#include "Core_Enum.h"
#include "Core_Struct.h"

namespace Core
{
	class CollisionComponent;
	Interface IColliderReceiver
	{
		virtual void NotifyActorBlock(CollisionComponent* pOtherComponent) PURE;
		virtual void NotifyActorBeginOverlap(CollisionComponent* pOtherComponent) PURE;
		virtual void NotifyActorEndOverlap(CollisionComponent* pOtherComponent) PURE;
	};
}