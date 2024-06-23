#pragma once
#include "Core_Define.h"
#include "Core_Type.h"

namespace LAYER
{
	enum LayerIndex : int
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