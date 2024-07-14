#pragma once
#include "Core_Define.h"
#include "Core_Enum.h"
#include "Core_Struct.h"

namespace Core
{
	Interface IInputReceiver
	{
		virtual void OnInputReceived(const InputEvent& inputEvent) PURE;
	};
}