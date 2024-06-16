#pragma once
#include "Core_Define.h"
#include "Core_Type.h"

enum LayerGroup : int
{
	BACKGROUND,
	BACKOBJECT,
	OBJECT,
	FRONTOBJECT,
	UI,
	END
};

enum BufferIndex : _uint
{
	BACKBUFFER = 0,
	FRONTBUFFER,
	BUFFER_END
};