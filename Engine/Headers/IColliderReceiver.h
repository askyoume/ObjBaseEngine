#pragma once
#include "Core_Define.h"
#include "Core_Enum.h"
#include "Core_Struct.h"

namespace Core
{
	struct CollisionPackage;
	Interface IColliderReceiver
	{
		virtual void NotifyActorBlock(CollisionPackage Components) PURE;
		virtual void NotifyActorBeginOverlap(CollisionPackage Components) PURE;
		virtual void NotifyActorEndOverlap(CollisionPackage Components) PURE;
	};
}