#include "CameraActor.h"
#include "CameraComponent.h"

void Core::CameraActor::Tick(_float deltaTime)
{
	Actor::Tick(deltaTime);
}

bool Core::CameraActor::Initialize()
{
	_cameraComponent = CameraComponent::Create();
	_cameraComponent->SetOwner(this);
	SetRootComponent(_cameraComponent);

	_vecComponents.push_back(_cameraComponent);

    return true;
}

Core::CameraActor* Core::CameraActor::Create()
{
	CameraActor* pInstance = new CameraActor;
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}
