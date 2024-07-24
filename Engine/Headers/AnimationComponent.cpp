#include "AnimationComponent.h"
#include "CoreManager.h"
#include "Texture.h"
#include "Actor.h"
#include "ACollision.h"

#undef min
#undef max

void Core::AnimationComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);

	if (_isVisible == false) { return; }
	if (0 == _currentFrame) { _isFrameEnd = false; }

	_currentFrameTime += deltaSeconds;
	
	if (_currentFrameTime >= _frameTime)
	{
		_currentFrameTime -= _frameTime;
		_prevFrame = _currentFrame;

		if (_isLoop)
		{
			_currentFrame = (_currentFrame + 1) % _frameCount;
		}
		else
		{
			_currentFrame = std::min(_currentFrame + 1, _frameCount - 1);
		}
	}

	if (_prevFrame != _currentFrame && _currentFrame == _frameCount - 1)
	{
		_isFrameEnd = true;
	}
	else
	{
		_isFrameEnd = false;
	}
}

void Core::AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (_isVisible == false) { return; }

	Texture* pTexture = GetOwner()->GetFrame(_currentClipIndex);

	SetTextureRect(pTexture);

	SetBitmapLocalTransform();

	Mathf::Matrix3x2 flipMatrix = Matx::Identity;

	if (_isFlip)
	{
		flipMatrix = D2D1::Matrix3x2F::Scale(-1, 1, 
				D2D1::Point2F(_textureRect.right * 0.5f, _textureRect.bottom * 0.5f)) * _localTransform;
	}
	else
	{
		flipMatrix = _localTransform;
	}

	Mathf::Matrix3x2 Transform = flipMatrix * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);

	pRenderTarget->DrawBitmap((*pTexture)[_currentFrame]);

	pRenderTarget->SetTransform(Matx::Identity);
}

void Core::AnimationComponent::AddClip(_pstring clipName, _float frameTime, bool isLoop)
{
	if(!_isInLayer)
	{
		AddRenderQueueInLayer();
		_isInLayer = true;
	}

	AnimationClip* pClip = new AnimationClip(clipName);
	pClip->frameTime = frameTime;
	pClip->clipIndex = (int)GetOwner()->GetTextureSize();
	pClip->isLoop = isLoop;

	_vecClips.insert(std::make_pair(clipName, pClip));
	
	::Core::CoreManager* pCore = ::Core::CoreManager::GetInstance();
	_bstr_t convertOwnerName = GetOwner()->GetName();
	_bstr_t convertName = clipName;
	_bstr_t textureName = convertOwnerName + "_" + convertName;
	
	GetOwner()->AddTexture(pCore->FindTexture(textureName));
}

const bool Core::AnimationComponent::IsClipPlay(_pstring clipName) const
{
	if (_currentClipName && !strcmp(_currentClipName, clipName))
	{
		return !_isFrameEnd;
	}

	return false;
}

const bool Core::AnimationComponent::IsClipEnd(_pstring clipName) const
{
	if (_currentClipName && !strcmp(_currentClipName, clipName))
	{
		return _isFrameEnd;
	}

	return true;
}

const bool Core::AnimationComponent::IsFrameEnd() const
{
	return _isFrameEnd;
}

void Core::AnimationComponent::SetPlayClip(_pstring clipName)
{
	_currentClipName = clipName;
	_currentClipIndex = _vecClips[clipName]->clipIndex;
	_frameTime = _vecClips[clipName]->frameTime;
	_isLoop = _vecClips[clipName]->isLoop;

	Texture* pTexture = GetOwner()->GetFrame(_currentClipIndex);

	_frameCount = pTexture->GetImageCount();

	_currentFrame = 0;
	_prevFrame = 0;
}

void Core::AnimationComponent::RemoveClip(_pstring clipName)
{
	_vecClips.erase(clipName);
}

bool Core::AnimationComponent::Initialize()
{
	BitmapComponent::Initialize();

    return true;
}

void Core::AnimationComponent::Remove()
{
	for (auto& clip : _vecClips)
	{
		delete clip.second;
	}

	_vecClips.clear();

	BitmapComponent::Remove();
}

Core::AnimationComponent* Core::AnimationComponent::Create()
{
	AnimationComponent* pInstance = new AnimationComponent();
	if (pInstance->Initialize())
		return pInstance;

    return nullptr;
}
