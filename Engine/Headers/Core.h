#pragma once
#include "Core_Define.h"
//#include "KhalaSystem.h"

namespace Core
{
	class Core abstract
	{
	protected:
		explicit Core() = default;
		virtual ~Core() = default;

	public:
		void Release()
		{
			Remove();
			delete this;
		}

	protected:
		virtual void Remove() PURE;
	};
}