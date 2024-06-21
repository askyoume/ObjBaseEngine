#pragma once
#include "Core_Define.h"

namespace KhalaSpace
{
	class KhalaBase abstract
	{
	protected:
		explicit KhalaBase() : KhalaID(++UID) {}
		virtual ~KhalaBase() DEFAULT;

	public:
		_uint GetKhalaID() const { return KhalaID; }

	private:
		static _uint UID;
		_uint KhalaID;
	};
}

_uint KhalaSpace::KhalaBase::UID = 0;