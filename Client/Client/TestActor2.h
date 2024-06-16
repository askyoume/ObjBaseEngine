#pragma once
#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Client
{
	class TestActor2 : public Core::Actor
	{
	protected:
		explicit TestActor2() DEFAULT;
		virtual ~TestActor2() DEFAULT;
	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

	public:
		static TestActor2* Create() { return new TestActor2; }

	private:
		void Remove() override;

	private:
		Mathf::Vector2 _position{ 0,0 };
	};
}