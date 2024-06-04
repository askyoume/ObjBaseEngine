#pragma once
#include "Core_Define.h"

namespace Core
{
	class TimeManager : public Core
	{
	private:
		TimeManager() DEFAULT;
		~TimeManager() DEFAULT;

	public:
		bool Initialize();
		void UpdateTick();
		_float GetTick() const;

	public:
		static TimeManager* Create();

	private:
		void Remove() override;

	private:
		LARGE_INTEGER tick{}, prevTick{}, frameTick{};
		float tickTime = 0.f;
	};
}