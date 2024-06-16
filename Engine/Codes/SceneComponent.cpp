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
	//��� ��ġ, ȸ��, �������� �������� ��ȯ ����� �����.
	//���� ��ǥ���� ����(��Ʈ���� �߾�)�� �������� �����Ѵ�.(ȸ����, ��ü�� �߾� ��ǥ)
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
		//Convert Based on Parent(�θ� ������� �θ��� ���� ��ǥ�� �������� ��ȯ)
		_WorldTransform = _parent->_WorldTransform * _RelativeTransform;
	}
	else
	{
		//�θ� ���� ��� ���� ��ǥ��� ����
		_WorldTransform = _RelativeTransform;
	}

	//Convert Based on Center Axis(������ �߾����� �������� ��ȯ)
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
