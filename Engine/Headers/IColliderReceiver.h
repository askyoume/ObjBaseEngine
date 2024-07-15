#pragma once
#include "Core_Define.h"
#include "Core_Enum.h"
#include "Core_Struct.h"

namespace Core
{
	class Actor;
	Interface IColliderReceiver
	{
		virtual void NotifyActorBlock(Actor* pOther) PURE;
		virtual void NotifyActorBeginOverlap(Actor* pOther) PURE;
		virtual void NotifyActorEndOverlap(Actor* pOther) PURE;
	};
}