#include "SceneComponent.h"
#include "CoreManager.h"
#include "Mathf.h"

void Core::SceneComponent::TickComponent(_float deltaTime)
{
	UpdateTransform();
	UpdateVelocity();
}

void Core::SceneComponent::UpdateTransform()
{
	//상대 위치, 회전, 스케일을 기준으로 변환 행렬을 만든다.
	//로컬 좌표계의 중점(비트맵의 중앙)을 기준으로 보정한다.(회전축, 객체의 중앙 좌표)
	_RelativeTransform = 
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(_RelativeScale.x, _RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(_RelativeRotation, D2D1::Point2F(_LocalLocation.x, _LocalLocation.y)) *
		D2D1::Matrix3x2F::Translation(
			_RelativeLocation.x - _LocalLocation.x, 
			_RelativeLocation.y + _LocalLocation.y
		);

	_CenterTransform = CoreManager::GetInstance()->GetCenterTransform();

	if (_parent)
	{
		//Convert Based on Parent(부모가 있을경우 부모의 월드 좌표계 기준으로 변환)
		_WorldTransform = _parent->_WorldTransform * _RelativeTransform;
	}
	else
	{
		//부모가 없을 경우 월드 좌표계로 대입
		_WorldTransform = _RelativeTransform;
	}

	//Convert Based on Center Axis(윈도우 중앙축을 기준으로 변환)
	_MidCalculateTransform = _WorldTransform * _CenterTransform;

}

void Core::SceneComponent::UpdateVelocity()
{
	if (_parent)
	{
		_ComponentVelocity += _parent->GetVelocity();
	}
}

void Core::SceneComponent::AttachToComponent(SceneComponent* pParent)
{
	if (_parent)
	{
		_parent->_children.erase(
			std::find(_parent->_children.begin(), _parent->_children.end(), this));
	}

	_parent = pParent;
	_parent->_children.push_back(this);
}
