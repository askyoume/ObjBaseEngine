#pragma once
#include "Core_Define.h"
#include "Component.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class SceneComponent abstract : public Component
	{
	protected:
		explicit SceneComponent() DEFAULT;
		virtual ~SceneComponent() DEFAULT;

	public:
		virtual void BeginPlay() override {};
		virtual void TickComponent(_float deltaTime) override;
		virtual void EndPlay() override {};

	public:
		void UpdateTransform();
		void UpdateVelocity();
		void SetRelativeScale(const Mathf::Vector2& scale) { _RelativeScale = scale; }
		void AddRelativeScale(const Mathf::Vector2& scale) { _RelativeScale += scale; }
		const Mathf::Vector2& GetRelativeScale() const { return _RelativeScale; }

		void SetRelativeRotation(float rotation) { _RelativeRotation = rotation; }
		void AddRelativeRotation(float rotation);
		float GetRelativeRotation() const { return _RelativeRotation; }

		void SetRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation = location; }
		void AddRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation += location; }
		const Mathf::Vector2& GetRelativeLocation() const { return _RelativeLocation; }

		void SetParentSceneComponent(SceneComponent* parent) { _parent = parent; }

		const Mathf::Matrix3x2& GetWorldTransform() const { return _WorldTransform; }
		const Mathf::Vector2& GetWorldLocation() const;
		void AttachToComponent(SceneComponent* pParent);
		void SetVelocity(const Mathf::Vector2& velocity) { _Velocity = velocity; }
		const Mathf::Vector2& GetVelocity() const { return _Velocity; }

	protected:
		virtual bool Initialize() PURE;
		virtual void Remove() PURE;

	protected:
		SceneComponent*				 _parent = nullptr;
		std::vector<SceneComponent*> _children;

	protected:
		//BoxCollider _BoxCollider;
		Mathf::Vector2		_LocalLocation{ UnitVector::Zero };
		Mathf::Vector2		_WorldLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeScale{ UnitVector::One };
		float				_RelativeRotation{ 0.f };
		Mathf::Matrix3x2	_RelativeTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Matrix3x2	_WorldTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Vector2		_Velocity{ UnitVector::Zero };
	};
}