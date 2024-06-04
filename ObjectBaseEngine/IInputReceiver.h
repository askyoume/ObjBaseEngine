#pragma once
#include "Core_Define.h"
#include "Core_Enum.h"
#include "Core_Struct.h"

namespace Core
{
	class IInputReceiver
	{
	protected:
		explicit IInputReceiver() DEFAULT;
		virtual ~IInputReceiver() DEFAULT;
	public:
		virtual void OnInputReceived(const InputEvent& inputEvent) PURE;
	};
}