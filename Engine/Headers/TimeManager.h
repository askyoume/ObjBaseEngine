#pragma once
#include "Core_Define.h"

namespace Core
{
	class TimeManager : public Core
	{
	private:
		TimeManager() = default;
		~TimeManager() = default;

	public:
		using _clock = std::chrono::high_resolution_clock;
		using _duration = std::chrono::duration<float>;
		using _timePoint = std::chrono::high_resolution_clock::time_point;

	public:
		bool Initialize();
		void UpdateTick();
		void SetTimeScale(_float timeScale);

	public:
		int GetFPS() const;
		_float GetDeltaSeconds() const;
		_float GetTimeScale() const;

	public:
		static TimeManager* Create();

	private:
		void Remove() override;

	private:
		//LARGE_INTEGER tick{}, prevTick{}, frameTick{};
		_timePoint _prevTick{};
		float _deltaSeconds{ 0.f };
		float _timeScale{ 1.0f };
		//float _timeScale{ 0.5f };
	};
}