#pragma once
#include "Core_Define.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class Transform abstract
	{
	protected:
		explicit Transform() DEFAULT;
		virtual ~Transform() DEFAULT;

	public:
		virtual void UpdateTransform() PURE;
		virtual void UpdateVelocity() PURE;

		//Local Offset�� ����Ҷ� ���
		void SetLocalLocation(const Mathf::Vector2& location) { _LocalLocation = location; }
		const Mathf::Vector2& GetLocalLocation() const { return _LocalLocation; }

		//��� ������ ��
		void SetRelativeScale(const Mathf::Vector2& scale) { _RelativeScale = scale; }
		void AddRelativeScale(const Mathf::Vector2& scale) { _RelativeScale += scale; }
		const Mathf::Vector2& GetRelativeScale() const { return _RelativeScale; }

		//��� ȸ��
		void SetRelativeRotation(float rotation) { _RelativeRotation = rotation; }
		void AddRelativeRotation(float rotation);
		float GetRelativeRotation() const { return _RelativeRotation; }

		//��� ��ġ
		void SetRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation = location; }
		void AddRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation += location; }
		const Mathf::Vector2& GetRelativeLocation() const { return _RelativeLocation; }

		//��� ��ġ�� �������� ȸ��, ������, ��ġ�� ������ ���
		const Mathf::Matrix3x2& GetWorldTransform() const { return _WorldTransform; }
		Mathf::Vector2 GetWorldLocation();

		//�ӵ� �� ���⺤��
		void SetVelocity(const Mathf::Vector2& velocity) { _ComponentVelocity = velocity; }
		const Mathf::Vector2& GetVelocity() const { return _ComponentVelocity; }
	
	protected:
		Mathf::Matrix3x2	_LocalTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Matrix3x2	_ViewTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Matrix3x2	_MidCalculateTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Matrix3x2	_CenterTransform{ D2D1::Matrix3x2F::Identity() }; //������ �߾����� �������� ��ȯ
		Mathf::Matrix3x2	_RelativeTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Matrix3x2	_WorldTransform{ D2D1::Matrix3x2F::Identity() };
		Mathf::Vector2		_LocalScale{ UnitVector::Zero };
		Mathf::Vector2		_LocalLocation{ UnitVector::Zero };
		Mathf::Vector2		_WorldLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeScale{ UnitVector::One };
		Mathf::Vector2		_ComponentVelocity{ UnitVector::Zero };
		float				_RelativeRotation{ 0.f };
		float				_LocalRotation{ 0.f };
	};
}