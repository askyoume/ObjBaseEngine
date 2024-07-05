#include "CameraComponent.h"
#include "CoreManager.h"
#include "ACollision.h"

void Core::CameraComponent::TickComponent(_float deltaTime)
{
	SceneComponent::TickComponent(deltaTime);
}

void Core::CameraComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CoreManager* _pCore = CoreManager::GetInstance();
	_pCore->GetGraphicsPackage()->_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));

	float collisionOffsetX = _pCollision->GetCollisionOffset().x;
	float collisionOffsetY = _pCollision->GetCollisionOffset().y;
	//TODO: Debug Code
	std::cout << "Camera Collision Offset : " << collisionOffsetX << " " << collisionOffsetY << std::endl;

	_pCollision->SetCollisionOffset({collisionOffsetX, collisionOffsetY});
	//Mathf::Vector2 point = { _WorldLocation.x, _WorldLocation.y };
	Mathf::Vector2 point = { collisionOffsetX, collisionOffsetY };
	pRenderTarget->DrawLine(D2D1::Point2F(point.x - 5.0f, point.y), D2D1::Point2F(point.x + 5.0f, point.y), _pCore->GetGraphicsPackage()->_pBrush, 10.0f);
	pRenderTarget->DrawLine(D2D1::Point2F(point.x, point.y - 5.0f), D2D1::Point2F(point.x, point.y + 5.0f), _pCore->GetGraphicsPackage()->_pBrush, 10.0f);

	Mathf::Rect collisionRect = {
		(_pCollision->GetCollisionOffset().x - _pCollision->GetCollisionSize().x * 0.5f),
		(_pCollision->GetCollisionOffset().y - _pCollision->GetCollisionSize().y * 0.5f),
		(_pCollision->GetCollisionOffset().x + _pCollision->GetCollisionSize().x * 0.5f),
		(_pCollision->GetCollisionOffset().y + _pCollision->GetCollisionSize().y * 0.5f)
	};

	pRenderTarget->DrawRectangle(D2D1::RectF(collisionRect.left, collisionRect.top, collisionRect.right, collisionRect.bottom), _pCore->GetGraphicsPackage()->_pBrush, 2.0f);
}

bool Core::CameraComponent::CheckCollision(ACollision* pCollision)
{
	return _pCollision->CheckCollision(pCollision);
}

bool Core::CameraComponent::Initialize()
{
	_pCollision = ACollision::Create();

	CoreManager* _pCore = CoreManager::GetInstance();

	float halfWidth = _pCore->GetWidth() * 0.5f;
	float halfHeight = _pCore->GetHeight() * 0.5f;

	_pCollision->SetCollisionSize({ _pCore->GetWidth(), _pCore->GetHeight() });
	_pCollision->SetCollisionOffset({halfWidth, halfHeight});

	return true;
}

Core::CameraComponent* Core::CameraComponent::Create()
{
	CameraComponent* pInstance = new CameraComponent();
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}
