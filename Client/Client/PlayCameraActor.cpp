#include "../../Engine/Headers/CoreManager.h"
#include "../../Engine/Headers/World.h"
#include "../../Engine/Headers/SceneComponent.h"
#include "../../Engine/Headers/CameraComponent.h"
#include "../../Engine/Headers/AnimationComponent.h"

#include "PlayCameraActor.h"

void Client::PlayCameraActor::BeginPlay()
{
	::Core::CoreManager* _pCoreManager = ::Core::CoreManager::GetInstance();
	_pOwnerWorld = _pCoreManager->GetWorld();
	_width = _pCoreManager->GetWidth();
	_height = _pCoreManager->GetHeight();
	_halfWidth = _width * 0.5f;
	_halfHeight = _height * 0.5f;
	//_pActorOne = _pOwnerWorld->FindActor("Player1");
	//_pActorTwo = _pOwnerWorld->FindActor("Player2");
	//test Code
	_pActorOne = _pOwnerWorld->FindActor("Aoko");
	_pActorOneAnimationComponent = _pActorOne->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	_pActorTwo = _pOwnerWorld->FindActor("Neko");
	_pActorTwoAnimationComponent = _pActorTwo->GetComponent<::Core::AnimationComponent>("AnimationComponent");
	_isTracking = true;
	//test Code end
}

void Client::PlayCameraActor::Tick(_float deltaSeconds)
{
	if (!_isTracking)
		return;

	if (!_pOwnerWorld)
		return;

	Actor::Tick(deltaSeconds);

	Mathf::Rect worldSize = _pOwnerWorld->GetWorldSize();
	_playerOneLocation = _pActorOne->GetRootComponent()->GetRelativeLocation();
	_playerTwoLocation = _pActorTwo->GetRootComponent()->GetRelativeLocation();
	
    float direction = _playerOneLocation.x - _playerTwoLocation.x;
    if(0.f > direction)
    {
		_pActorOneAnimationComponent->SetFlip(false);
		_pActorTwoAnimationComponent->SetFlip(true);
	}
	else
	{
		_pActorOneAnimationComponent->SetFlip(true);
		_pActorTwoAnimationComponent->SetFlip(false);
    }

	Mathf::Vector2 parentLocation = Mathf::Vector2{ (_playerTwoLocation.x + _playerOneLocation.x) * 0.5f, _playerOneLocation.y };
	Mathf::Vector2 cameraCenter = Mathf::Vector2{ _halfWidth, _halfHeight };
	Mathf::Vector2 cameraOffset = _cameraComponent->GetCameraOffset();
	Mathf::Vector2 cameraLocation = _cameraComponent->GetRelativeLocation();

	_cameraLerpFactor = fmin(8.0f, _cameraLerpFactor + deltaSeconds * 0.1f);

    if (!_isOneClamp && !_isTwoClamp)
    {
        Mathf::Vector2 targetLocation = (parentLocation - cameraCenter - cameraOffset);
        Mathf::Vector2 newLocation = Mathf::Lerp(cameraLocation, targetLocation, _cameraLerpFactor * deltaSeconds);

        if (targetLocation != _oldLocation)
        {
            _isMove = true;
        }
        else
        {
            _isMove = false;
        }

        if (0 != worldSize.bottom && 0 != worldSize.right)
        {
            if (newLocation.x - _halfWidth < worldSize.left)
            {
                newLocation.x = worldSize.left + _halfWidth;
                _isMove = false;
            }
            else if (newLocation.x + _halfWidth > worldSize.right)
            {
                newLocation.x = worldSize.right - _halfWidth;
                _isMove = false;
            }

            if (newLocation.y - _halfHeight < worldSize.top)
            {
                newLocation.y = worldSize.top + _halfHeight;
                _isMove = false;
            }
            else if (newLocation.y + _halfHeight > worldSize.bottom)
            {
                newLocation.y = worldSize.bottom - _halfHeight;
                _isMove = false;
            }
        }

        _cameraComponent->SetRelativeLocation(newLocation);
        _oldLocation = targetLocation;
    }

    PlayerLocationClamp();
}

Client::PlayCameraActor* Client::PlayCameraActor::Create()
{
	PlayCameraActor* pInstance = new PlayCameraActor;
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}

void Client::PlayCameraActor::PlayerLocationClamp()
{
    Mathf::Vector2 cameraLocation = _cameraComponent->GetRelativeLocation();
	const float frameLimit = 100.f;
    float minX = cameraLocation.x + frameLimit;
    float maxX = cameraLocation.x + _width - frameLimit;

    _playerOneLocation.x = fmax(minX, fmin(_playerOneLocation.x, maxX));
    _isOneClamp = (_playerOneLocation.x == minX || _playerOneLocation.x == maxX);

    _playerTwoLocation.x = fmax(minX, fmin(_playerTwoLocation.x, maxX));
    _isTwoClamp = (_playerTwoLocation.x == minX || _playerTwoLocation.x == maxX);

    _pActorOne->GetRootComponent()->SetRelativeLocation(_playerOneLocation);
    _pActorTwo->GetRootComponent()->SetRelativeLocation(_playerTwoLocation);
}
