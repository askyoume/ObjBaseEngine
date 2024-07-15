#include "BoxComponent.h"
#include "CoreManager.h"
#include "Actor.h"

void Core::BoxComponent::TickComponent(_float deltaTime)
{
	SceneComponent::TickComponent(deltaTime);
	//_pCollision->SetCollisionSize(_size);
	Mathf::Vector2 worldLocation = GetWorldLocation();
	_pCollision->SetCollisionOffset(worldLocation);
}

bool Core::BoxComponent::IsCollision(CollisionComponent* pOther)
{
	if (pOther->GetColliderType() == Collider::COLLIDER_AABB)
	{
		BoxComponent* pBox = dynamic_cast<BoxComponent*>(pOther);
		if (pBox)
		{
			return _pCollision->CheckCollision(pBox->_pCollision);
		}
	}

	return false;
}

void Core::BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	Mathf::Matrix3x2 Transform = _cameraMatrix;
	pRenderTarget->SetTransform(Transform);

	Mathf::Vector2 point = {
		_pCollision->GetCollisionOffset().x,
		_pCollision->GetCollisionOffset().y
	};

	ID2D1SolidColorBrush* m_pBrush = CoreManager::GetInstance()->GetGraphicsPackage()->_pBrush;
	
	pRenderTarget->DrawLine(D2D1::Point2F(point.x - 5.0f, point.y), D2D1::Point2F(point.x + 5.0f, point.y), m_pBrush, 3.0f);
	pRenderTarget->DrawLine(D2D1::Point2F(point.x, point.y - 5.0f), D2D1::Point2F(point.x, point.y + 5.0f), m_pBrush, 3.0f);

	Mathf::Rect rect = {
		point.x - _pCollision->GetCollisionSize().x * 0.5f,
		point.y - _pCollision->GetCollisionSize().y * 0.5f,
		point.x + _pCollision->GetCollisionSize().x * 0.5f,
		point.y + _pCollision->GetCollisionSize().y * 0.5f
	};

	pRenderTarget->DrawRectangle(D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom), m_pBrush, 3.0f);
}

void Core::BoxComponent::SetOffset(const Mathf::Vector2& offsetVector)
{
	_pCollision->SetCollisionOffset(offsetVector);
}

void Core::BoxComponent::SetSize(const Mathf::Vector2& sizeVector)
{
	_pCollision->SetCollisionSize(sizeVector);
}

bool Core::BoxComponent::Initialize()
{
	_pCollision = ACollision::Create();
	if (!_pCollision)
	{
		return false;
	}

	_collider = Collider::COLLIDER_AABB;
	_type = Collision::COLLISION_BLOCK;

	return true;
}

void Core::BoxComponent::Remove()
{
	SafeRelease(_pCollision);
}

Core::BoxComponent* Core::BoxComponent::Create()
{
	BoxComponent* pInstance = new BoxComponent;
	if (pInstance->Initialize())
	{
		return pInstance;
	}

	return nullptr;
}
