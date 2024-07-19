#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/SceneComponent.h"
#include "../../Engine/Headers/CameraComponent.h"

#include "PlayCameraActor.h"

void Client::PlayCameraActor::BeginPlay()
{
	//_pActorOne = _pOwnerWorld->FindActor("Player1");
	//_pActorTwo = _pOwnerWorld->FindActor("Player2");
	::Core::CoreManager* _pCoreManager = ::Core::CoreManager::GetInstance();
	_pOwnerWorld = _pCoreManager->GetWorld();
	//test Code
	_pActorOne = _pOwnerWorld->FindActor("Aoko");
	_pActorTwo = _pOwnerWorld->FindActor("Neko");
	_isTracking = true;
	//test Code end
}

void Client::PlayCameraActor::Tick(_float deltaTime)
{
	if (!_isTracking)
		return;

	if (!_pOwnerWorld)
		return;

	Actor::Tick(deltaTime);

	::Core::CoreManager* _pCoreManager = ::Core::CoreManager::GetInstance();

	Mathf::Rect worldSize = _pOwnerWorld->GetWorldSize();
	float halfWidth = _pCoreManager->GetWidth() / 2.f;
	float halfHeight = _pCoreManager->GetHeight() / 2.f;

	/*Mathf::Vector2 parentLocation = _pParent->GetRootComponent()->GetRelativeLocation();*/
	Mathf::Vector2 PlayerOneLocation = _pActorOne->GetRootComponent()->GetRelativeLocation();
	Mathf::Vector2 PlayerTwoLocation = _pActorTwo->GetRootComponent()->GetRelativeLocation();
	Mathf::Vector2 parentLocation = Mathf::Vector2{(PlayerOneLocation.x - PlayerTwoLocation.x) * 2.f, PlayerOneLocation.y};
	//Mathf::Vector2 cameraCenter = _cameraComponent->GetCenterPosition();
	Mathf::Vector2 cameraCenter = Mathf::Vector2{ halfWidth, halfHeight };
	Mathf::Vector2 cameraOffset = _cameraComponent->GetCameraOffset();
	Mathf::Vector2 cameraLocation = _cameraComponent->GetRelativeLocation();

	_cameraLerpFactor = fmin(8.0f, _cameraLerpFactor + deltaTime * 0.001f);

	Mathf::Vector2 targetLocation = ( parentLocation - cameraCenter - cameraOffset );
	Mathf::Vector2 newLocation = Mathf::Lerp(cameraLocation, targetLocation, _cameraLerpFactor * deltaTime);

	if (targetLocation != _oldLocation)
	{
		_isMove = true;
	}
	else
	{
		_isMove = false;
	}

	if (targetLocation.x > _oldLocation.x)
	{
		_moveDirectionFlag = MoveDirectionFlag::Right;
	}
	else if (targetLocation.x < _oldLocation.x)
	{
		_moveDirectionFlag = MoveDirectionFlag::Left;
	}
	else if (targetLocation.y > _oldLocation.y)
	{
		_moveDirectionFlag = MoveDirectionFlag::Down;
	}
	else if (targetLocation.y < _oldLocation.y)
	{
		_moveDirectionFlag = MoveDirectionFlag::Up;
	}
	else
	{
		_moveDirectionFlag = 0;
	}

	if(0 != worldSize.bottom && 0 != worldSize.right)
	{
		if (newLocation.x - halfWidth < worldSize.left)
		{
			newLocation.x = worldSize.left + halfWidth;
			_isMove = false;
		}

		if (newLocation.x + halfWidth > worldSize.right)
		{
			newLocation.x = worldSize.right - halfWidth;
			_isMove = false;
		}

		if (newLocation.y - halfHeight < worldSize.top)
		{
			newLocation.y = worldSize.top + halfHeight;
			_isMove = false;
		}

		if (newLocation.y + halfHeight > worldSize.bottom)
		{
			newLocation.y = worldSize.bottom - halfHeight;
			_isMove = false;
		}
	}

	_cameraComponent->SetRelativeLocation(newLocation);
	_oldLocation = targetLocation;
}

Client::PlayCameraActor* Client::PlayCameraActor::Create()
{
	PlayCameraActor* pInstance = new PlayCameraActor;
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}
