#include "SceneComponent.h"

void Core::SceneComponent::TickComponent(_float deltaTime)
{
	UpdateTransform();
	UpdateVelocity();
}

void Core::SceneComponent::UpdateTransform()
{
	_RelativeTransform = 
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(_RelativeScale.x, _RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(_RelativeLocation.x,_RelativeLocation.y);

	if (_parent)
	{
		_WorldTransform = _RelativeTransform * _parent->_WorldTransform;
	}
	else
	{
		_WorldTransform = _RelativeTransform;
	}

}

void Core::SceneComponent::UpdateVelocity()
{
	if (_parent)
	{
		_Velocity += _parent->GetVelocity();
	}
}

void Core::SceneComponent::AddRelativeRotation(float rotation)
{
	_RelativeRotation += rotation;
	_RelativeRotation = fmodf(_RelativeRotation, 360.f);
}

const Vector2& Core::SceneComponent::GetWorldLocation() const
{
	Vector2 result{ UnitVector::Zero };
	result.x = _WorldTransform._31;
	result.y = _WorldTransform._32;
	return result;
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
