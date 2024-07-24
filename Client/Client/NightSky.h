#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Client
{
	class NightSky : public Core::Actor
	{
	protected:
		explicit NightSky() = default;
		virtual ~NightSky() = default;
	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static NightSky* Create() { return new NightSky; }
	};
}