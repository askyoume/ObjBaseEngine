#pragma once

#include "../../Engine/Headers/Core_Define.h"
#include "../../Engine/Headers/Actor.h"

namespace Client
{
	class TestActor : public Core::Actor
	{
	protected:
		explicit TestActor() DEFAULT;
		virtual ~TestActor() DEFAULT;
	public:
		void BeginPlay() override;
		void Tick(_float deltaTime) override;
		void Fixed() override;
		void EndPlay() override;

		//testCode
		void Fire();
		void Rotate(float degree);
		void Move(float x, float y);

	public:
		static TestActor* Create() { return new TestActor; }

	private:
		void Remove() override;

	private:
		Mathf::Vector2 _position{ 0,0 };
	};
}