#pragma once
#include "Core.h"
#include "Core_Define.h"

namespace Core
{
	class Object abstract : public Core
	{
	protected:
		explicit Object() : instanceID(++ID) {}
		virtual ~Object() = default;

	public:
		_uint GetInstanceID() const { return instanceID; }
		_pstring GetName() const { return name; }
		void SetName(const _pstring& name) { this->name = name; }
				
	public:
		void OnDestroyMark(bool isMark) { this->_isMark = isMark; }
		bool IsDestroyMarked() const { return  _isMark; }
		void CreateObjectDirectory();

	protected:
		virtual void Remove() override PURE;

	protected:
		_pstring name = nullptr;

	private:
		static _uint ID;
		_uint instanceID;
		bool _isMark = false;
	};
}
