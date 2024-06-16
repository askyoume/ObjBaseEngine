#include "TimeManager.h"

#include <profileapi.h>
#include <cmath>

bool Core::TimeManager::Initialize()
{
	QueryPerformanceFrequency(&tick);
	QueryPerformanceCounter(&prevTick);

	return true;
}

void Core::TimeManager::UpdateTick()
{
	QueryPerformanceCounter(&frameTick);
	tickTime = (_float)(frameTick.QuadPart - prevTick.QuadPart) / tick.QuadPart;
	prevTick = frameTick;
}

_float Core::TimeManager::GetTick() const
{
	return tickTime;
}

int Core::TimeManager::GetFPS() const
{
	return (int)round(1.f / tickTime);
}

Core::TimeManager* Core::TimeManager::Create()
{
	return new TimeManager();
}

void Core::TimeManager::Remove()
{
}
