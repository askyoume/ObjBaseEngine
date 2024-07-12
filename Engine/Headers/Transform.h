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

		//상대 스케일 값
		void SetRelativeScale(const Mathf::Vector2& scale) { _RelativeScale = scale; }
		void AddRelativeScale(const Mathf::Vector2& scale) { _RelativeScale += scale; }
		const Mathf::Vector2& GetRelativeScale() const { return _RelativeScale; }

		//상대 회전
		void SetRelativeRotation(float rotation) { _RelativeRotation = rotation; }
		void AddRelativeRotation(float rotation);
		float GetRelativeRotation() const { return _RelativeRotation; }

		//상대 위치
		void SetRelativeY(float y) { _RelativeLocation.y = y; }
		void SetRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation = location; }
		void AddRelativeLocation(const Mathf::Vector2& location) { _RelativeLocation += location; }
		const Mathf::Vector2& GetRelativeLocation() const { return _RelativeLocation; }

		//상대 위치를 기준으로 회전, 스케일, 위치를 적용한 행렬
		const Mathf::Matrix3x2& GetWorldTransform() const { return _WorldTransform; }
		Mathf::Vector2 GetWorldLocation();

		//속도 및 방향벡터
		void SetVelocity(const Mathf::Vector2& velocity) { _ComponentVelocity = velocity; }
		const Mathf::Vector2& GetVelocity() const { return _ComponentVelocity; }
	
	protected:
		Mathf::Matrix3x2	_MidCalculateTransform{ Matx::Identity };
		Mathf::Matrix3x2	_CenterTransform{ Matx::Identity }; //윈도우 중앙축을 기준으로 변환
		Mathf::Matrix3x2	_RelativeTransform{ Matx::Identity };
		Mathf::Matrix3x2	_WorldTransform{ Matx::Identity };
		Mathf::Vector2		_WorldLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeLocation{ UnitVector::Zero };
		Mathf::Vector2		_RelativeScale{ UnitVector::One };
		Mathf::Vector2		_ComponentVelocity{ UnitVector::Zero };
		float				_RelativeRotation{ 0.f };
		float				_LocalRotation{ 0.f };
	};
}