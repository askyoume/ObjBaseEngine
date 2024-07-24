#include "SceneComponent.h"
#include "CoreManager.h"
#include "Mathf.h"

void Core::SceneComponent::TickComponent(_float deltaSeconds)
{
	UpdateTransform();
	UpdateVelocity();
}

void Core::SceneComponent::UpdateTransform()
{
	_RelativeTransform = 
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(_RelativeScale.x, _RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(_RelativeLocation.x, _RelativeLocation.y);

	if (_parent)
	{
		//Convert Based on Parent(부모가 있을경우 부모의 월드 좌표계 기준으로 변환)
		_WorldTransform =_RelativeTransform * _parent->_WorldTransform;
	}
	else
	{
		//부모가 없을 경우 월드 좌표계로 대입
		_WorldTransform = _RelativeTransform;
	}

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
