#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Client
{
	class Moon : public Core::Actor
	{
	protected:
		explicit Moon() = default;
		virtual ~Moon() = default;
	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static Moon* Create() { return new Moon; }
	};
}