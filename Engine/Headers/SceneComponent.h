#pragma once
#include "Core_Define.h"
#include "Component.h"
#include "Mathf.h"
#include "Transform.h"

namespace Core
{
	CORECLASS()
	class SceneComponent : public Component, public Transform
	{
	protected:
		explicit SceneComponent() DEFAULT;
		virtual ~SceneComponent() DEFAULT;

	public:
		//Component
		virtual void BeginPlay() override {};
		virtual void TickComponent(_float deltaTime) override;
		virtual void EndPlay() override {};

	public:
		//SceneComponent
		void AttachToComponent(SceneComponent* pParent);

	public:
		//Transform
		void UpdateTransform() override;
		void UpdateVelocity() override;

	protected:
		virtual bool Initialize(){ return true; }
		virtual void Remove(){};

	protected:
		SceneComponent*				 _parent = nullptr;
		std::vector<SceneComponent*> _children;

	public:
		static SceneComponent* Create() { return new SceneComponent; }

	};
}