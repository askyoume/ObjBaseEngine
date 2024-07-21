#pragma once
#include "Core_Define.h"
#include "Core_Type.h"

namespace LAYER
{
	enum LayerIndex : _uint
	{
		BACKGROUND = 0,
		BACKOBJECT,
		OBJECT,
		FRONTOBJECT,
		UI,
		END
	};
}

enum BufferIndex : _uint
{
	BACKBUFFER = 0,
	FRONTBUFFER,
	BUFFER_END
};

namespace Collider
{
	enum ColliderType
	{
		COLLIDER_NONE = -1,
		COLLIDER_AABB = 0,
		COLLIDER_OBB,
		COLLIDER_SPHERE,
		COLLIDER_END
	};
}

namespace Collision
{
	enum CollisionType
	{
		COLLISION_IGNORE = 0,
		COLLISION_OVERLAP,
		COLLISION_BLOCK,
		COLLISION_END
	};
}
