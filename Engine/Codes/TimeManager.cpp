#include "TimeManager.h"
//#include <profileapi.h>
//#include <cmath>

bool Core::TimeManager::Initialize()
{
	/*QueryPerformanceFrequency(&tick);
	QueryPerformanceCounter(&prevTick);*/

	_prevTick = _clock::now();

	return true;
}

void Core::TimeManager::UpdateTick()
{
	/*QueryPerformanceCounter(&frameTick);
	tickTime = (_float)(frameTick.QuadPart - prevTick.QuadPart) / tick.QuadPart;
	prevTick = frameTick;*/

	auto currentTick = _clock::now();
	_duration duration = currentTick - _prevTick;
	_deltaSeconds = duration.count() * _timeScale;
	_prevTick = currentTick;
}

_float Core::TimeManager::GetDeltaSeconds() const
{
	return _deltaSeconds;
}

int Core::TimeManager::GetFPS() const
{
	return static_cast<int>(round(1.f / _deltaSeconds));
}

void Core::TimeManager::SetTimeScale(_float timeScale)
{
	_timeScale = timeScale;
}

_float Core::TimeManager::GetTimeScale() const
{
	return _timeScale;
}

Core::TimeManager* Core::TimeManager::Create()
{
	return new TimeManager();
}

void Core::TimeManager::Remove()
{
}
