#include "CameraActor.h"
#include "CameraComponent.h"

void Core::CameraActor::Tick(_float deltaTime)
{
	if (!_isTracking)
		return;

	Actor::Tick(deltaTime);

	Mathf::Vector2 parentLocation = _pParent->GetRootComponent()->GetRelativeLocation();
	Mathf::Vector2 cameraCenter = _cameraComponent->GetCenterPosition();
	Mathf::Vector2 cameraOffset = _cameraComponent->GetCameraOffset();
	Mathf::Vector2 cameraLocation = _cameraComponent->GetRelativeLocation();

	Mathf::Vector2 targetLocation = ( parentLocation - cameraCenter - cameraOffset );
	Mathf::Vector2 newLocation = Mathf::Lerp(cameraLocation, targetLocation, _cameraLerpFactor * deltaTime);

	_cameraComponent->SetRelativeLocation(newLocation);
}

void Core::CameraActor::TrackTarget(Actor* pTarget)
{
	_pParent = pTarget;
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
