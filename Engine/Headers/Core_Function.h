#pragma once
#include "Core_Define.h"
#include "Core.h"

namespace Core
{
	template <typename T>
	class has_Release
	{
	public:
		static constexpr bool value = std::is_base_of<Core, T>::value;
	};


	template <typename T, typename std::enable_if<has_Release<T>::value, int>::type = 0>
	void SafeDelete(T*& ptr)
	{
		if (ptr)
		{
			ptr->Release();
			ptr = nullptr;
		}
	}

	template <typename T, typename std::enable_if<!has_Release<T>::value, int>::type = 0>
	void SafeDelete(T*& ptr) = delete;

	template <typename T>
	void SafeRelease(T* ptr)
	{
		if (ptr)
		{
			ptr->Release();
			ptr = nullptr;
		}
	}

}