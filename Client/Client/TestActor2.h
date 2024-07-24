#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Client
{
	class TestActor2 : public Core::Actor
	{
	protected:
		explicit TestActor2() = default;
		virtual ~TestActor2() = default;
	public:
		void BeginPlay() override;
		void Tick(_float deltaSeconds) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static TestActor2* Create() { return new TestActor2; }
	};
}