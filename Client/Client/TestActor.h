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
		void Render(ID2D1RenderTarget* pRenderTarget) override;
		void EndPlay() override;

		//testCode
		void Fire();

	public:
		static TestActor* Create() { return new TestActor; }

	private:
		void Remove() override;
	};
}