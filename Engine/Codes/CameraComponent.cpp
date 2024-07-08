#include "CameraComponent.h"
#include "CoreManager.h"
#include "ACollision.h"

void Core::CameraComponent::TickComponent(_float deltaTime)
{
	SceneComponent::TickComponent(deltaTime);
	CoreManager* _pCore = CoreManager::GetInstance();

	float Width = _pCore->GetWidth();
	float Height = _pCore->GetHeight();

	float halfWidth = Width * 0.5f;
	float halfHeight = Height * 0.5f;

	Mathf::Vector2 CollisionPosition = 
	{ _RelativeLocation.x + Width, _RelativeLocation.y + Height};

	_pCollision->SetCollisionSize({ Width, Height });
	_pCollision->SetCollisionOffset(CollisionPosition);

	std::cout << "Camera Position : " << CollisionPosition.x << " " << CollisionPosition.y << std::endl;
}

bool Core::CameraComponent::CheckCollision(ACollision* pCollision)
{
	return _pCollision->CheckCollision(pCollision);
}

bool Core::CameraComponent::Initialize()
{
	_pCollision = ACollision::Create();

	return true;
}

void Core::CameraComponent::Remove()
{
	_pCollision->Release();
	_pCollision = nullptr;
}

Core::CameraComponent* Core::CameraComponent::Create()
{
	CameraComponent* pInstance = new CameraComponent();
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}
